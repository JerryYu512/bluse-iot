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
 * @file boot_signal.h
 * @brief 
 * @author wotsen (astralrovers@outlook.com)
 * @version 1.0.0
 * @date 2021-08-15
 * 
 * @copyright MIT License
 * 
 */
#pragma once
#include <functional>
#include <map>
#include <signal.h>

namespace biot {

enum : int {
	signal_abrt = SIGABRT,
	signal_bus = SIGBUS,
	signal_fpe = SIGFPE,
	signal_ill = SIGILL,
	signal_int = SIGINT,
	signal_segv = SIGSEGV,
	signal_term = SIGTERM,
	signal_pipe = SIGPIPE,
	signal_usr1 = SIGUSR1,
	signal_usr2 = SIGUSR2,
};

/// 信号处理函数类型
using signal_handler_t = std::function<void(int, siginfo_t *, void*)>;

/**
 * @brief 信号
 * 
 */
class Signal {
public:
	typedef struct {
		signal_handler_t handle;
		void *ud;
	} sig_reg_t;

	/// 信号注册处理函数
	static void signal_reg(int sig, signal_handler_t fun, void *arg);

	~Signal();

private:
	Signal();

	static void default_signal_handler(int sig);
	static void signal_handler(int sig, siginfo_t *info, void *arg);

public:
	static std::map<int, sig_reg_t> handle_;	///< 信号处理
};

} // namespace biot
