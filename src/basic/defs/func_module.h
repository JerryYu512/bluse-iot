/**
 * MIT License
 * 
 * Copyright © 2022 <Jerry.Yu>.
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software
 * and associated documentation files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the
 * 
 * The above copyright notice and this permission notice shall be included in all copies or
 * substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS";, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
 * BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 * 
 * @file func_module.h
 * @brief 
 * @author Jerry.Yu (jerry.yu512outlook.com)
 * @version 1.0.0
 * @date 2022-05-08
 * 
 * @copyright MIT License
 * 
 */
#pragma once
#include <string>
#include <functional>
#include <stdint.h>

namespace biot {

// 主类型
enum {
	FUNC_MODULE_MAIN_NON = 0,
	FUNC_MODULE_MAIN_HARDWARE = 0x10000,
	FUNC_MODULE_MAIN_DEVICE = 0x20000,
	FUNC_MODULE_MAIN_NETWORK = 0x30000,
	FUNC_MODULE_MAIN_DATABASE = 0x40000,
	FUNC_MODULE_MAIN_MEDIA = 0x50000,
	FUNC_MODULE_MAIN_ALGO = 0x60000,
	FUNC_MODULE_MAIN_SUBSYS = 0x70000,
} E_FUNC_MODULE_MAIN_TYPE;

#define FUNC_MODULE_SUB_TYPE(type) ((type) & 0xffff)
#define FUNC_MODULE_MAIN_TYPE(type) ((type) & 0xffff0000)
#define FUNC_MODULE_TYPE(main, sub) (((main) & 0xffff0000) | ((sub) & 0xffff))

#define FUNC_MODULE_HW_TYPE(sub) FUNC_MODULE_TYPE(FUNC_MODULE_MAIN_HARDWARE, sub)
#define FUNC_MODULE_DEV_TYPE(sub) FUNC_MODULE_TYPE(FUNC_MODULE_MAIN_DEVICE, sub)
#define FUNC_MODULE_NET_TYPE(sub) FUNC_MODULE_TYPE(FUNC_MODULE_MAIN_NETWORK, sub)
#define FUNC_MODULE_DB_TYPE(sub) FUNC_MODULE_TYPE(FUNC_MODULE_MAIN_DATABASE, sub)
#define FUNC_MODULE_MEDIA_TYPE(sub) FUNC_MODULE_TYPE(FUNC_MODULE_MAIN_MEDIA, sub)
#define FUNC_MODULE_ALGO_TYPE(sub) FUNC_MODULE_TYPE(FUNC_MODULE_MAIN_ALGO, sub)
#define FUNC_MODULE_SUBSYS_TYPE(sub) FUNC_MODULE_TYPE(FUNC_MODULE_MAIN_SUBSYS, sub)

// 网络次类型
enum {
	FUNC_MODULE_SUB_NET_NON = FUNC_MODULE_MAIN_NON,

	// 基础网络次类型0x0001-0x1000
	FUNC_MODULE_SUB_NET_BASIC = 0x0001,
	// 网络应用0x1001-0x2000
	FUNC_MODULE_SUB_NET_APP_WEB = 0x1001,
} E_FUNC_MODULE_SUB_NET_TYPE;

// 模块启动结果
enum : int {
	FUNC_MODULE_START_OK = 0,
	FUNC_MODULE_START_FAILED,
	FUNC_MODULE_START_REBOOT,
} FUNC_MODULE_START_RET;

// 模块状态
enum : int {
	FUNC_MODULE_STATE_NOT_INIT = 0,

	FUNC_MODULE_STATE_SETUP,
	FUNC_MODULE_STATE_RUNNING,
	FUNC_MODULE_STATE_STOP,
	FUNC_MODULE_STATE_ERROR,
} FUNC_MODULE_STATE;

// 应用模块定义
typedef struct func_module_s {
	std::string name;				///< 模块名
	std::string description;		///< 模块描述
	uint64_t type;					///< 模块类型
	std::function<int(void)> run;	///< 启动接口
	std::function<int(void)> state;	///< 获取状态 @ref FUNC_MODULE_STATE
	// func_module_s() {}
	// func_module_s(const std::string& name, const std::string& desc, uint64_t type, std::function<int(void)> run, std::function<int(void)> st)
	// : name(name), description(desc), type(type), run(run), state(st) {}
} func_module_t;

} // namespace biot
