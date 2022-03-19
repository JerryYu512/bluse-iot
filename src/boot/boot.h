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
#include <string>
#include <vector>

namespace biot {

/**
 * @brief 启动结果
 * 
 */
enum : int {
	BOOT_OK,        ///< 启动成功
	BOOT_FAILD,     ///< 启动失败
	BOOT_REBOOT,    ///< 需要重启程序
    BOOT_NONE,      ///< 无操作
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
    std::string name;       ///< 启动项
    std::string desc;       ///< 描述
	int (*boot)(void);      ///< 启动接口
	void (*release)(void);  ///< 释放接口
    int result;             ///< 启动结果
    boot_s(const char* name, const char* desc, int(*boot)(void), void(*release)(void))
    : name(name), desc(desc), boot(boot), release(release), result(BOOT_NONE) {}
} boot_t;

/**
 * @brief 启动
 * 
 * @param boots 
 * @return int 
 */
int biot_boot(std::vector<boot_t>& boots);

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

} // namespace biot
