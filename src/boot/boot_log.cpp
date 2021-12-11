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

#include "log/ars_iot_log.h"
#include "core/version.h"

namespace ars {

namespace iot {

int boot_log(void) {
	// 日志初始化
#ifdef DEBUG
	ars::iot::set_logger(ARS_IOT_LOG_DEF_NAME, ars::iot::log_trace);
#else
	ars::iot::set_logger(ARS_IOT_LOG_DEF_NAME, ars::iot::log_info);
#endif

#ifdef DEBUG
	spdlog::flush_on(spdlog::level::trace);
#endif

	ARSIOT_INFO("{:<30}{}{}", "[application name", 			"] ==> ", 	"ars-iot[ars iot app]");
	ARSIOT_INFO("{:<30}{}{}", "[compile time", 				"] ==> ", 	app_compile_time());
	ARSIOT_INFO("{:<30}{}{}", "[application version", 		"] ==> ", 	app_version());
	ARSIOT_INFO("{:<30}{}{}", "[application edition", 		"] ==> ", 	app_edition());
	ARSIOT_INFO("{:<30}{}{}", "[application identifier", 	"] ==> ", 	app_identifier());
	ARSIOT_INFO("{:<30}{}{}", "[aplication author", 		"] ==> ", 	"Jerry.Yu(astralrovers#outlook.com)");
	ARSIOT_INFO("{:<30}{}{}", "[copyright", 				"] ==> ", 	"MIT");

	return BOOT_OK;
}

void boot_un_log(void) {
	ars::iot::release_logger();
}

} // namespace iot

} // namespace ars
