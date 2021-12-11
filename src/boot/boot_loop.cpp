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
 * @file boo_loop.cpp
 * @brief 
 * @author wotsen (astralrovers@outlook.com)
 * @version 1.0.0
 * @date 2021-08-15
 * 
 * @copyright MIT License
 * 
 */
#include "boot.h"
#include "log/ars_iot_log.h"
#include <chrono>
#include <thread>
#include <mutex>
#include <condition_variable>

namespace ars {

namespace iot {

/**
 * @brief 启动循环
 * 
 */
class BootLoop {
public:
	BootLoop() : st_(boot_state_run) {}

public:
	boot_loop_state_t st_;				///< 状态
	std::mutex mtx_;					///< 锁
	std::condition_variable cond_;		///< 条件
};

// 循环示例
static BootLoop bloop;

boot_loop_state_t boot_loop_state(void) {
	return bloop.st_;
}

void boot_loop_state_change(boot_loop_state_t state) {
	{
		std::unique_lock<std::mutex> lck(bloop.mtx_);
		bloop.st_ = state;
	}
	bloop.cond_.notify_one();
}

int boot_loop(void) {
	while (bloop.st_ != boot_state_exit) {
		{
			std::unique_lock<std::mutex> lck(bloop.mtx_);
			// 停止时就一直休眠
			while (bloop.st_ == boot_state_stop) {
				bloop.cond_.wait(lck);
			}
		}

		// 退出
		if (bloop.st_ == boot_state_exit) {
			ARSIOT_INFO("ars-iot loop exit.");
		}

		// 正常心跳
		std::this_thread::sleep_for(std::chrono::seconds(5));
		ARSIOT_INFO("ars-iot loop heartbeat.");
	}

	return BOOT_OK;
}

void boot_un_loop(void) {

}

} // namespace iot

} // namespace ars
