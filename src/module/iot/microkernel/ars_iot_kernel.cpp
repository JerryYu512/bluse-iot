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
 * @file ars_iot_kernel.cpp
 * @brief 
 * @author wotsen (astralrovers@outlook.com)
 * @version 1.0.0
 * @date 2021-08-09
 * 
 * @copyright MIT License
 * 
 */
#include "ars_iot_kernel.h"

namespace ars {

namespace iot {

///< 内核初始化
kernel_error_t kernel_init(kernel_t &kernel, dev_basic_info_t &dev_info, kernel_config_t &conf);

kernel_error_t kernel_start(kernel_t &kernel) {
	kernel.run_state = kernel_run_st_start;
	// TODO:入队启动事件，用于通知到每个扩展模块
	return kerr_success;
}

kernel_error_t kernel_stop(kernel_t &kernel);
kernel_error_t kernel_finit(kernel_t &kernel);

///< 内核调度
kernel_error_t kernel_core_yield(kernel_t &kernel);

///< 内核用户任务调度
kernel_error_t kernel_core_yield_user(kernel_t &kernel);

///< 网络操作
///< opname: 1.绑定网卡，3.断开重连
kernel_error_t kernel_set_net_option(kernel_t &kernel, int opname, const void *opval, int oplen);

///< 发送消息
kernel_error_t kernel_send_msg(kernel_t &kernel, kernel_pubmsg_t *pubmsg);
kernel_error_t kernel_send_msg_async(kernel_t &kernel, kernel_pubmsg_t *pubmsg);

} // namespace iot

} // namespace ars
