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
 * @file ars_iot_kernel_log.h
 * @brief 
 * @author wotsen (astralrovers@outlook.com)
 * @version 1.0.0
 * @date 2021-08-01
 * 
 * @copyright MIT License
 * 
 */
#pragma once

namespace ars {

namespace iot {

/**
 * @brief 内核日志等级
 * 
 */
typedef enum {
	klog_none,
	klog_trance,
	klog_debug,
	klog_info,
	klog_warn,
	klog_error,
} kernel_log_level;

///< 内核日志
typedef void (*kernel_log_cb)(kernel_log_level level, int err_code, int sub_code, const char *msg);

/**
 * @brief 内核日志接口
 * 
 * @param ctx 
 * @param level 等级
 * @param fname 文件名
 * @param fun 函数名
 * @param line 行号
 * @param err_code 错误码
 * @param sub_code 子错误码
 * @param fmt 格式
 * @param ... 
 */
void kernel_log(void *ctx, kernel_log_level level, const char *fname, const char *fun, int line, int err_code, int sub_code, const char *fmt, ...);

} // namespace iot

} // namespace ars
