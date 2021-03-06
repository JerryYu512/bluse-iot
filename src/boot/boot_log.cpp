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
 * @file boot_log.cpp
 * @brief 
 * @author wotsen (astralrovers@outlook.com)
 * @version 1.0.0
 * @date 2021-08-15
 * 
 * @copyright MIT License
 * 
 */
#include "boot.h"

#include "basic/log/biot_log.h"
#include "config/version.h"
#include "config/args_dec.h"

namespace biot {

// 转换启动时，命令行输入的日志等级
static biot::biot_log_level trans_log_level(void);

static biot::biot_log_level trans_log_level(void) {
	switch (FLG_debug_lv) {
		case 0:
			return biot::log_trace;
		case 1:
			return biot::log_debug;
		case 2:
			return biot::log_trace;
		case 3:
			return biot::log_warn;
		case 4:
			return biot::log_err;
		case 5:
			return biot::log_critical;
		case 6:
			return biot::log_off;
		default:
			return biot::log_info;
	}
}

int boot_log(void) {
	// 日志初始化
	biot::init_log();
	biot::set_log_level(BIOT_LOG_DEFAULT, trans_log_level());

#ifdef DEBUG
	// spdlog::flush_on(spdlog::level::trace);
#endif

	BIOT_INFO("{:<30}{}{}", "[application name", 			"] ==> ", 	"bluse-iot[bluse iot app]");
	BIOT_INFO("{:<30}{}{}", "[compile time", 				"] ==> ", 	app_compile_time());
	BIOT_INFO("{:<30}{}{}", "[application version", 		"] ==> ", 	app_std_version());
	BIOT_INFO("{:<30}{}{}", "[application edition", 		"] ==> ", 	app_edition());
	BIOT_INFO("{:<30}{}{}", "[application identifier", 		"] ==> ", 	app_identifier());
	BIOT_INFO("{:<30}{}{}", "[aplication author", 			"] ==> ", 	"Jerry.Yu(astralrovers@outlook.com)");
	BIOT_INFO("{:<30}{}{}", "[copyright", 					"] ==> ", 	"MIT");

	return BOOT_OK;
}

void boot_un_log(void) {
}

} // namespace biot
