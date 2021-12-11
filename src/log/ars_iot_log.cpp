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
 * @file ars_iot_log.cpp
 * @brief 
 * @author wotsen (astralrovers@outlook.com)
 * @version 1.0.0
 * @date 2021-08-14
 * 
 * @copyright MIT License
 * 
 */
#include "ars_iot_log.h"
#include "spdlog/spdlog.h"
#include "spdlog/async.h"
#include "spdlog/sinks/base_sink.h"
#include "spdlog/sinks/rotating_file_sink.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "arss/str/pystring.hpp"
#include "config/args_dec.h"
#include "config/configure.h"

namespace ars {

namespace iot {

std::string get_log_default_path(void) {
	std::string log_path = FLG_abs_rt_path;
	log_path = pystring::os::path::join(log_path, IOT_LOG_PATH);
	log_path = pystring::os::path::join(log_path, ARS_IOT_DEF_LOG_FILENAME);

	return log_path;
}

void set_logger(const char *log_name, ars_iot_log_level level, const char *filename, size_t max_file_size, size_t max_files)
{
	if (!log_name) {
		return ;
	}

	auto old = spdlog::get(log_name);

	if (old) {
		// 如果是注册过的，那么修改等级
		old->set_level((spdlog::level::level_enum)level);
	} else {
		if (!filename) {
			// 仅仅输出到控制台
			auto console_log = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
			auto logger = std::make_shared<spdlog::logger>(log_name, spdlog::sinks_init_list{console_log});
			logger->set_level((spdlog::level::level_enum)level);
			// https://github.com/gabime/spdlog/wiki/3.-Custom-formatting
			logger->set_pattern("[%Y-%m-%d %H:%M:%S.%e][%^%l%$][%n][%t][%@:%!] %v");
			spdlog::register_logger(logger);
			if (strcmp(log_name, ARS_IOT_LOG_DEF_NAME) == 0) {
				spdlog::set_default_logger(logger);
			}
		} else {
			// 控制台
			auto console_log = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
			// 文件
			auto file_log = std::make_shared<spdlog::sinks::rotating_file_sink_mt>(filename, max_file_size, max_files);
			auto logger = std::make_shared<spdlog::logger>(log_name, spdlog::sinks_init_list{console_log, file_log});
			logger->set_level((spdlog::level::level_enum)level);
			logger->set_pattern("[%Y-%m-%d %H:%M:%S.%e][%^%l%$][%n][%t][%@:%!] %v");
			spdlog::register_logger(logger);
			if (strcmp(log_name, ARS_IOT_LOG_DEF_NAME) == 0) {
				spdlog::set_default_logger(logger);
			}
			// TODO:tcp
		}
	}
}

} // namespace iot

} // namespace ars
