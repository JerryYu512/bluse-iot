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
 * @file boot_module.cpp
 * @brief 
 * @author wotsen (astralrovers@outlook.com)
 * @version 1.0.0
 * @date 2021-08-15
 * 
 * @copyright MIT License
 * 
 */
#include <vector>
#include "boot.h"
#include "basic/log/biot_log.h"

// 模块头文件
#include "basic/defs/func_module.h"
#include "module/module_interface.h"

namespace biot {

static func_module_t func_modules[] = {
	{"webapp", "程序HTTP-API服务", FUNC_MODULE_NET_TYPE(FUNC_MODULE_SUB_NET_APP_WEB), webapp_start, webapp_state},
};

int boot_module(void) {
	for (auto &item : func_modules) {
		int ret = item.run();
		if (FUNC_MODULE_START_OK == ret) {
			BIOT_DEBUG("func module \"{}\" start ok\n", item.name);
		} else if (FUNC_MODULE_START_FAILED == ret) {
			BIOT_ERROR("func module \"{}\" start faild\n", item.name);
		} else if (FUNC_MODULE_START_REBOOT == ret) {
			BIOT_ERROR("func module \"{}\" start faild, need reboot\n", item.name);
			return BOOT_REBOOT;
		} else {}
	}
	return BOOT_OK;
}

void boot_un_module(void) {

}

} // namespace biot
