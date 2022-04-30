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
 * @file boot_signal.cpp
 * @brief 
 * @author wotsen (astralrovers@outlook.com)
 * @version 1.0.0
 * @date 2021-08-15
 * 
 * @copyright MIT License
 * 
 */
#include "boot_signal.h"
#include <string.h>
#include <unistd.h>
#include <stdio.h>

namespace biot {

///< 信号映射
typedef struct {
	int signal;			///< 信号编号
	const char *name;	///< 信号名称
} signal_t;

static const signal_t signals[] = {
	{ signal_abrt, "SIGABRT" },
	{ signal_bus, "SIGBUS" },
	{ signal_fpe, "SIGFPE" },
	{ signal_ill, "SIGILL" },
	{ signal_int, "SIGINT" },
	{ signal_segv, "SIGSEGV" },
	{ signal_term, "SIGTERM" },
	{ signal_pipe, "SIGPIPE" },
	{ signal_usr1, "SIGUSR1" },
	{ signal_usr2, "SIGUSR2" },
};

std::map<int, Signal::sig_reg_t> Signal::handle_;

void Signal::signal_handler(int sig, siginfo_t *info, void *arg) {
	auto item = handle_.find(sig);

	// 没找到的就忽略
	if (item == handle_.end()) {
		for (const auto& s : signals) {
			if (s.signal == sig) {
				printf("ignore signal : %d ==> %s\n", s.signal, s.name);
				return;
			}
		}
		printf("ignore signal : %d ==> null\n", sig);
		return ;
	}

	if (item->second.handle) {
		// 使用注册接口
		item->second.handle(sig, info, item->second.ud);
	} else {
		// 默认方式
		default_signal_handler(sig);
	}
}

Signal::Signal() {
	struct sigaction sig_action;

	memset(&sig_action, 0, sizeof(sig_action));

	sigemptyset(&sig_action.sa_mask);
	sig_action.sa_flags |= SA_SIGINFO;
	sig_action.sa_sigaction = &signal_handler;
	for (const auto& s : signals) {
		sigaction(s.signal, &sig_action, nullptr);
	}
}

Signal::~Signal() {}

void Signal::default_signal_handler(int sig) {
	struct sigaction sig_action;

	memset(&sig_action, 0, sizeof(sig_action));
	sigemptyset(&sig_action.sa_mask);
	sig_action.sa_handler = SIG_DFL;
	sigaction(sig, &sig_action, nullptr);
	kill(getpid(), sig);
}

void Signal::signal_reg(int sig, signal_handler_t fun, void *arg) {
	static Signal sig_instance;
	Signal::sig_reg_t reg = {
		fun,
		arg,
	};
	handle_[sig] = reg;
}

} // namespace biot
