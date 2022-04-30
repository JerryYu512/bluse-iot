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
 * @file main.cpp
 * @brief 
 * @author wotsen (astralrovers@outlook.com)
 * @version 1.0.0
 * @date 2021-08-08
 * 
 * @copyright MIT License
 * 
 */
#include "basic/log/biot_log.h"
#include "basic/base/biot_time.h"
#include <iostream>
#include <iomanip>
#include <string>
#include "config/configure.h"
#include "config/version.h"
#include "hv/hbase.h"
#include "hv/htime.h"
#include "hv/hflag.h"
#include "boot/boot.h"

static std::string get_pwd(void);

// 命令行参数
DEF_string(abs_rt_path, get_pwd(), "application runtime abslution path");
DEF_uint64(log_filesize, BIOT_LOG_MAX_FILESIZE, "log file max size");
DEF_uint32(log_filenum, BIOT_LOG_FILE_MAX_NUM, "log file max num");

// 启动项
static const char* const boot_result[] = {
	"success", "failed", "reboot", "none",
};

static std::vector<biot::boot_t> boots = {
	{"prepare", "基本资源准备", biot::boot_pre, biot::boot_un_pre},
	{"log", "日志初始化", biot::boot_log, biot::boot_un_log},
	{"env", "程序运行环境", biot::boot_env, biot::boot_un_env},
	{"configure", "配置参数", biot::boot_parameter, biot::boot_un_parameter},
	{"basic", "基本功能", biot::boot_basic, biot::boot_un_basic},
	{"modules", "应用模块", biot::boot_module, biot::boot_un_module},
};

// 获取当前路径
static std::string get_pwd(void) {
	char buf[256] = "";
	return get_run_dir(buf, (int)sizeof(buf));
}

int main(int argc, char **argv) {
	hv::flag::init(argc, argv);

	std::cout << "-- Boot Application [BIOT] -- " << biot::time_now_str() << std::endl;
	std::cout << "-- Version                 -- " << biot::app_edition() << " (" << biot::app_base_version() << " - " << biot::app_std_version() << ") " << biot::app_compile_time() << std::endl << std::endl;

	if (biot::BOOT_REBOOT == biot::biot_boot(boots)) {
		exit(biot::BOOT_REBOOT);
	}

	biot_boot_printi("####################boot over#####################\n");
	for (auto &item : boots) {
		biot_boot_printi("--------------> [%s]-[%s]\n", item.name.c_str(), boot_result[item.result]);
	}
	biot_boot_printi("####################goto looping#####################\n");

	return 0;
}
