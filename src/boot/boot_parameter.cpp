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
 * @file boot_parameter.cpp
 * @brief 
 * @author wotsen (astralrovers@outlook.com)
 * @version 1.0.0
 * @date 2021-08-15
 * 
 * @copyright MIT License
 * 
 */
#include "boot.h"
#include "hv/pystring.h"
#include "hv/json.hpp"
#include "hv/hfile.h"
#include "hv/hbase.h"
#include "config/args_dec.h"
#include "config/configure.h"
#include "basic/log/biot_log.h"
#include "basic/base/biot_time.h"
#include "config/version.h"
#include "config/sec_param.h"
#include "config/param/param.h"
#include "config/param/param_patch.h"

namespace biot {

int boot_parameter(void) {
	// 固件参数
	if (read_sec_param()) {
		return BOOT_REBOOT;
	}

	// TODO:能力级

	// 初始化参数
	auto ret = init_app_param();
	if (ret) {
		return BOOT_REBOOT;
	}
	// 补丁
	ret = patch_common();
	ret = patch_for_product(get_sec_param().devtype);

	return 0;
}

void boot_un_parameter(void) {

}

} // namespace biot
