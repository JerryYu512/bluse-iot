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
 * @file main.cpp
 * @brief 
 * @author wotsen (astralrovers@outlook.com)
 * @version 1.0.0
 * @date 2021-08-08
 * 
 * @copyright MIT License
 * 
 */
#include "log/ars_iot_log.h"
#include <iostream>
#include <iomanip>
#include <string>
#include "arss/time/timestamp.hpp"
#include "arss/fs/file_util.hpp"
#include "arss/flag/flag.hpp"
#include "core/version.h"
#include "boot/boot.h"

static std::string get_pwd(void);

DEF_string(abs_rt_path, get_pwd(), "application runtime abslution path");

static std::string get_pwd(void) {
	char buf[256] = "";
	return arss::fs::run_dir(buf, (int)sizeof(buf));
}

int main(int argc, char **argv) {
	arss::flag::init(argc, argv);

	std::cout << "-- Boot Application Ars-IOT : " << arss::Timestamp::now().toFormattedString() << std::endl;
	std::cout << "-- Version-" << ars::iot::app_edition() << " : [" << ars::iot::app_version() << "] " << ars::iot::app_compile_time() << std::endl << std::endl;

	ARS_IOT_BOOT(pre);
	ARS_IOT_BOOT(parameter);
	ARS_IOT_BOOT(log);
	ARS_IOT_BOOT(basic);
	ARS_IOT_BOOT(module);
	ARS_IOT_BOOT(loop);

	return 0;
}
