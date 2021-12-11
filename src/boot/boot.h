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
 * @file boot.h
 * @brief 
 * @author wotsen (astralrovers@outlook.com)
 * @version 1.0.0
 * @date 2021-08-14
 * 
 * @copyright MIT License
 * 
 */
#pragma once
#include "log/ars_iot_log.h"

namespace ars {

namespace iot {

/**
 * @brief 启动结果
 * 
 */
enum : int {
	BOOT_OK,
	BOOT_FAILD,
	BOOT_REBOOT,
};

/**
 * @brief 循环状态
 * 
 */
typedef enum {
	boot_state_run,
	boot_state_stop,
	boot_state_exit,
} boot_loop_state_t;

/**
 * @brief boot程序对
 * 
 */
typedef struct boot_s {
	int (*boot)(void);
	void (*boot_un)(void);
} boot_t;

#define ARS_IOT_BOOT(name)                                  \
    {                                                       \
        int ret = ars::iot::boot_##name();                  \
        if (ars::iot::BOOT_OK == ret) {                     \
            ars::iot::boot_t boot = {nullptr, nullptr};     \
            boot.boot = ars::iot::boot_##name;              \
            boot.boot_un = ars::iot::boot_un_##name;        \
            boot_push(#name, boot);                         \
            iot_boot_printi("boot success [%s]\n", #name);  \
        } else if (ars::iot::BOOT_REBOOT == ret) {          \
            while (true) {                                  \
                ars::iot::boot_t boot = {nullptr, nullptr}; \
                if (!boot_pop(#name, boot)) {               \
                    break;                                  \
                } else {                                    \
                    if (boot.boot_un) {                     \
                        boot.boot_un();                     \
                    }                                       \
                }                                           \
            }                                               \
            iot_boot_printe("reboot by [%s]\n", #name);     \
            exit(ret);                                      \
        } else if (ars::iot::BOOT_FAILD == ret) {           \
            iot_boot_printe("boot faild [%s]\n", #name);    \
        } else {                                            \
        }                                                   \
    }

// boot入队
void boot_push(const char *name, boot_t &boot);
// boot出队
bool boot_pop(const char *name, boot_t &boot);

// 主线程循环状态
boot_loop_state_t boot_loop_state(void);
// 修改循环状态
void boot_loop_state_change(boot_loop_state_t state);

//////////////////////////////////////////////////////////////////////
/// boot begin
//////////////////////////////////////////////////////////////////////

// 准备阶段
// 目录、资源文件
int boot_pre(void);
void boot_un_pre(void);

// 日志
int boot_log(void);
void boot_un_log(void);

// 程序运行环境设置
int boot_env(void);
void boot_un_env(void);

// 参数
int boot_parameter(void);
void boot_un_parameter(void);

// 基本功能
// 基础全局配置
// 网络
int boot_basic(void);
void boot_un_basic(void);

// 模块
int boot_module(void);
void boot_un_module(void);

// 循环
int boot_loop(void);
void boot_un_loop(void);

//////////////////////////////////////////////////////////////////////
/// boot end
//////////////////////////////////////////////////////////////////////

} // namespace iot

} // namespace ars
