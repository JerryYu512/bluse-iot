/**
 * MIT License
 *
 * Copyright © 2021 <wotsen>.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software
 * and associated documentation files (the “Software”), to deal in the Software without
 * restriction, including without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the
 *
 * The above copyright notice and this permission notice shall be included in all copies or
 * substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
 * BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * @file boot_pre.cpp
 * @brief
 * @author wotsen (astralrovers@outlook.com)
 * @version 1.0.0
 * @date 2021-08-15
 *
 * @copyright MIT License
 *
 */
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <execinfo.h>
#include <iostream>
#include <sstream>
#include "arss/defs/defs.hpp"
#include "arss/flag/flag.hpp"
#include "arss/fs/file_util.hpp"
#include "arss/fs/file.hpp"
#include "arss/mix/singleton.hpp"
#include "arss/str/pystring.hpp"
#include "arss/os/coredump.hpp"
#include "arss/time/timestamp.hpp"
#include "arss/thread/current_thread.hpp"
#include "log/ars_iot_log.h"
#include "boot.h"
#include "boot_signal.h"
#include "config/args_dec.h"
#include "config/configure.h"

namespace ars {

namespace iot {

static bool create_runtime_dir(void);

/**
 * @brief 进程重复运行检测，只允许single模式
 *
 */
class AloneProccess {
private:
    /**
     * @brief Construct a new Alone Proccess object
     *
     * @param pid_file pid文件，用于检测
     */
    AloneProccess(const char *pid_file) : pid_(pid_file), fd_(-1) {
        fd_ = open(pid_file, O_RDWR | O_CREAT, 0666);
        if (fd_ < 0) {
            throw std::runtime_error(std::string("can not open pid file : ") + pid_file);
        }
    }
    ~AloneProccess() {
        if (fd_ > 0) {
            close(fd_);
        }
    }

public:
    static bool check(const char *pid_file) {
        static AloneProccess alone(pid_file);
        return alone.IsAlone();
    }

    /**
     * @brief 文件锁定
     *
     * @return true 锁定成功
     * @return false 锁定失败
     */
    bool LockFile(void) {
        struct flock fl;

        fl.l_type = F_WRLCK;  // 锁定文件，锁定失败则是已经运行了一个
        fl.l_start = 0;
        fl.l_whence = SEEK_SET;
        fl.l_len = 0;

        return fcntl(fd_, F_SETLK, &fl) == 0;
    }

    /**
     * @brief 进程single检测
     *
     * @return true single
     * @return false 非single
     */
    bool IsAlone(void) {
        if (!LockFile()) {
            if (errno == EACCES || errno == EAGAIN) {
                close(fd_);
                fd_ = -1;
                iot_boot_printe("proccessing is running!\n");
                return false;
            }
			iot_boot_printe("can't lock \"%s\", reason : %s\n", pid_.c_str(), strerror(errno));
        }

        char buf[16] = {'\0'};

        if (ftruncate(fd_, 0) != 0) {
			iot_boot_printe("ftruncate \"%s\", reason : %s\n", pid_.c_str(), strerror(errno));
            return false;
        }

        sprintf(buf, "%ld", (long)getpid());
        return write(fd_, buf, strlen(buf) + 1) > 0;
    }

    DISALLOW_COPY_AND_ASSIGN(AloneProccess);

private:
    std::string pid_;
    int fd_;
};

static bool create_runtime_dir(void) {
    const char *env_dirs[] = {
        IOT_RT_ROOT_PATH,
		IOT_ETC_PATH,
		IOT_DATA_PATH,
        IOT_USR_PATH,
		IOT_LOG_PATH,
		IOT_COREDUMP_PATH,
    };

    // 创建运行时目录
    for (size_t i = 0; i < ARSS_ARRAY_SIZE(env_dirs); i++) {
        std::string path = pystring::os::path::join(FLG_abs_rt_path, env_dirs[i]);
        iot_boot_printd("mkdir \"%s\"\n", path.c_str());
        if (arss::fs::mkdir_p(path.c_str()) < 0) {
            iot_boot_printe("mkdir \"%s\" failed\n", env_dirs[i]);
            return false;
        }
    }

    return true;
}

static void set_coredump(void) {
#ifdef DEBUG
    std::string path = pystring::os::path::join(FLG_abs_rt_path, IOT_COREDUMP_PATH);

	iot_boot_printi("setup coredump \"%s\"\n", path.c_str());
	arss::os::setup_coredump(path.c_str(), 1024 * 1024 * 1024);
#endif
}

static void save_core_trace(int sig, siginfo_t *info, void *arg) {
	// addr2line -Cfe [exe] -a [addr]
	arss::Timestamp t = arss::Timestamp::now();
	std::string fname = FLG_abs_rt_path;
	arss::fs::File f;
	std::ostringstream ostr;

	fname = pystring::os::path::join(fname, IOT_COREDUMP_PATH);
	fname = pystring::os::path::join(fname, "crash-" + std::string(arss::thread::t_threadName) + "-" + t.toFormattedFileString(true) + ".dump");

	if (f.open(fname.c_str(), "a") < 0) {
		return ;
	}

	int fd = f.get_fd()->fd.fd;

	// 文件锁定
	struct flock fl;
	fl.l_type = F_WRLCK;
	fl.l_start = 0;
	fl.l_whence = SEEK_SET;
	fl.l_len = 0;
	fl.l_pid = getpid();
	fcntl(fd, F_SETLKW, &fl);

	// 程序绝对路径
	char buf[4096] = "";
	int count = readlink("/proc/self/exe", buf, sizeof(buf));
	if (count > 0) {
		buf[count] = '\n';
		buf[count + 1] = 0;
		ostr << buf;
	}

	// 时间戳
	ostr << "Dump Time : " << t.toFormattedString(true) << std::endl;

	// 线程和信号
	ostr << "Curr thread: " << arss::thread::t_cachedTid << " " << arss::thread::t_threadName << ", Catch signal: " << sig << std::endl;

	// 堆栈
	void *dump[256] = {nullptr};
	int nsize = backtrace(dump, 256);

	ostr << "backtrace rank = " << nsize << std::endl;

	if (nsize > 0) {
		char **sym = backtrace_symbols(dump, nsize);
		if (sym) {
			for (int i = 0; i < nsize; i++) {
				ostr << sym[i] << std::endl;
			}
			free(sym);
		}
	}

	std::cout << ostr.str();
	f.write(ostr.str().c_str(), ostr.str().size());

	// 解锁
	fl.l_type = F_UNLCK;
	fcntl(fd, F_SETLK, &fl);

	ARSIOT_CRITICAL("\n{}", ostr.str());

    signal(sig, SIG_DFL);
    kill(getpid(), sig);
}

static void reg_signal(void) {
	Signal::signal_reg(signal_abrt, save_core_trace, nullptr);
	Signal::signal_reg(signal_bus, save_core_trace, nullptr);
	Signal::signal_reg(signal_fpe, save_core_trace, nullptr);
	Signal::signal_reg(signal_ill, save_core_trace, nullptr);
	Signal::signal_reg(signal_int, nullptr, nullptr);
	Signal::signal_reg(signal_segv, save_core_trace, nullptr);
	Signal::signal_reg(signal_term, nullptr, nullptr);
}

int boot_pre(void) {
    if (!AloneProccess::check(IOT_PID_FILENAME)) {
        return BOOT_REBOOT;
    }

    if (!create_runtime_dir()) {
        return BOOT_REBOOT;
    }

	set_coredump();

	reg_signal();

    return BOOT_OK;
}

void boot_un_pre(void) {}

}  // namespace iot

}  // namespace ars
