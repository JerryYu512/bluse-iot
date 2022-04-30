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
#include "biot_log.h"
#include "spdlog/spdlog.h"
#include "spdlog/async.h"
#include "spdlog/sinks/base_sink.h"
#include "spdlog/sinks/rotating_file_sink.h"
#include "spdlog/sinks/stdout_color_sinks.h"
// #include "spdlog/default_formatter.h"
#include "spdlog/pattern_formatter.h"
#include "hv/pystring.h"
#include "config/args_dec.h"
#include "config/configure.h"

namespace biot {

/**
 * @brief 模块日志配置
 * 
 */
typedef struct module_log_config_s {
	int index;					///< 索引
	const char* name;			///< 模块名称
	biot_log_level level;	///< 日志等级
	int method;					///< 输出方法
	std::shared_ptr<spdlog::logger> logger;	///< 实际句柄
} module_log_config_t;

/**
 * @brief Get the log default path object
 * 
 * @return std::string 
 */
static std::string get_log_default_path(void);

/**
 * @brief Get the log max filesize object
 * 
 * @return size_t 
 */
static size_t get_log_max_filesize(void);

/**
 * @brief Get the log max filenum object
 * 
 * @return size_t 
 */
static size_t get_log_max_filenum(void);

/// 模块日志配置列表
static module_log_config_t module_log_configure[BIOT_LOG_INDEX_MAX] = {
#define XX(idx, name, level, method) {BIOT_##idx, name, BIOT_##level, BIOT_##method, nullptr},
	BIOT_LOG_INDEX_MAP(XX)
#undef XX
};

biot_log_level get_log_level(int idx) {
	if (idx < 0 || idx >= BIOT_LOG_INDEX_MAX) {
		return log_n_levels;
	}

	return module_log_configure[idx].level;
}

std::shared_ptr<spdlog::logger> get_logger(int idx) {
	if (idx < 0 || idx >= BIOT_LOG_INDEX_MAX) {
		return nullptr;
	}

	return module_log_configure[idx].logger;
}

static std::string get_log_default_path(void) {
	std::string log_path = FLG_abs_rt_path;
	log_path = pystring::os::path::join(log_path, BIOT_LOG_PATH);
	log_path = pystring::os::path::join(log_path, BIOT_DEF_LOG_FILENAME);

	return log_path;
}

static size_t get_log_max_filesize(void) {
	return (size_t)FLG_log_filesize;
}

static size_t get_log_max_filenum(void) {
	return (size_t)FLG_log_filenum;
}

void init_log(void) {
	for (int i = 0; i < BIOT_LOG_INDEX_MAX; i++) {
		if (BIOT_LOG_METHOD_CONSOLE == module_log_configure[i].method) {
			// 仅仅输出到控制台
			auto console_log = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
			console_log->set_level((spdlog::level::level_enum)module_log_configure[i].level);
			// https://github.com/gabime/spdlog/wiki/3.-Custom-formatting
			console_log->set_formatter(std::make_unique<spdlog::pattern_formatter>("[%Y-%m-%d %H:%M:%S.%e][%^%l%$][%n][%t][%@:%!] %v"));
			auto logger = std::make_shared<spdlog::logger>(module_log_configure[i].name, spdlog::sinks_init_list{console_log});
			logger->set_level((spdlog::level::level_enum)module_log_configure[i].level);
			// register_logger(log_idx, logger);
			module_log_configure[i].logger = logger;
			if (BIOT_LOG_DEFAULT == i) {
				spdlog::set_default_logger(logger);
			}
		} else if (BIOT_LOG_METHOD_FILE == module_log_configure[i].method) {
			// FIXME:仅文件
			// 控制台
			auto console_log = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
			console_log->set_formatter(std::make_unique<spdlog::pattern_formatter>("[%Y-%m-%d %H:%M:%S.%e][%^%l%$][%n][%t][%@:%!] %v"));
			// 文件
			auto file_log = std::make_shared<spdlog::sinks::rotating_file_sink_mt>(get_log_default_path(), get_log_max_filesize(), get_log_max_filenum());
			file_log->set_formatter(std::make_unique<spdlog::pattern_formatter>("[%Y-%m-%d %H:%M:%S.%e][%^%l%$][%n][%t][%@:%!] %v"));
			auto logger = std::make_shared<spdlog::logger>(module_log_configure[i].name, spdlog::sinks_init_list{console_log, file_log});
			logger->set_level((spdlog::level::level_enum)module_log_configure[i].level);
			// logger->set_pattern("[%Y-%m-%d %H:%M:%S.%e][%^%l%$][%n][%t][%@:%!] %v");
			module_log_configure[i].logger = logger;
			if (BIOT_LOG_DEFAULT == i) {
				spdlog::set_default_logger(logger);
			}
		}
		// TODO:网络
	}
}

void set_log_level(int log_idx, biot_log_level level) {
	if (log_idx < 0 || log_idx >= BIOT_LOG_INDEX_MAX) {
		return ;
	}
	if (module_log_configure[log_idx].logger) {
		// 如果是注册过的，那么修改等级
		module_log_configure[log_idx].logger->set_level((spdlog::level::level_enum)level);
	}
}

} // namespace biot
