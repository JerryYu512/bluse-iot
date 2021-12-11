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
 * @file ars_iot_log.h
 * @brief 
 * @author wotsen (astralrovers@outlook.com)
 * @version 1.0.0
 * @date 2021-08-14
 * 
 * @copyright MIT License
 * 
 */
#pragma once
#ifdef DEBUG
#define SPDLOG_ACTIVE_LEVEL 0
#endif

#include <stdio.h>
#include "spdlog/spdlog.h"

#define ARS_IOT_LOG_DEF_NAME "ars-iot"
#define ARS_IOT_DEF_LOG_FILENAME "ars-iot.log"
// 20M
#define ARS_IOT_LOG_FILE_MAX_SIZE (20 * 1024 * 1024)
// 64个文件
#define ARS_IOT_LOG_FILE_MAX_NUM 64

// 模块名称
#ifndef ARS_IOT_LOG_NAME
#define ARS_IOT_LOG_NAME ARS_IOT_LOG_DEF_NAME
#endif

namespace ars {

namespace iot {

// 启动时的打印接口
#ifdef DEBUG
#define iot_boot_printd(fmt, ...) \
    printf("[BOOT][DEBUG][%s:%d:%s]" fmt, __FILE__, __LINE__, __func__, ##__VA_ARGS__)
#define iot_boot_verbose() printf("xxxxxx %s:%s:%d xxxxxx\n", __FILE__, __func__, __LINE__)
#else
#define iot_boot_printd(...)
#define iot_boot_verbose()
#endif

#define iot_boot_printi(fmt, ...) \
    printf("[BOOT][INFO][%s:%d:%s]" fmt, __FILE__, __LINE__, __func__, ##__VA_ARGS__)
#define iot_boot_printe(fmt, ...) \
    printf("[BOOT][ERROR][%s:%d:%s]" fmt, __FILE__, __LINE__, __func__, ##__VA_ARGS__)

// 运行时日志接口
#define ARSIOT_TRACE(...) ({auto log = spdlog::get(ARS_IOT_LOG_NAME); if (log) { SPDLOG_LOGGER_TRACE(spdlog::get(ARS_IOT_LOG_NAME), __VA_ARGS__); }; 0;}) 
#define ARSIOT_DEBUG(...) ({auto log = spdlog::get(ARS_IOT_LOG_NAME); if (log) { SPDLOG_LOGGER_DEBUG(spdlog::get(ARS_IOT_LOG_NAME), __VA_ARGS__); }; 0;}) 
#define ARSIOT_INFO(...) ({auto log = spdlog::get(ARS_IOT_LOG_NAME); if (log) { SPDLOG_LOGGER_INFO(spdlog::get(ARS_IOT_LOG_NAME), __VA_ARGS__); }; 0;}) 
#define ARSIOT_WARN(...) ({auto log = spdlog::get(ARS_IOT_LOG_NAME); if (log) { SPDLOG_LOGGER_WARN(spdlog::get(ARS_IOT_LOG_NAME), __VA_ARGS__); }; 0;}) 
#define ARSIOT_ERROR(...) ({auto log = spdlog::get(ARS_IOT_LOG_NAME); if (log) { SPDLOG_LOGGER_ERROR(spdlog::get(ARS_IOT_LOG_NAME), __VA_ARGS__); }; 0;}) 
#define ARSIOT_CRITICAL(...) ({auto log = spdlog::get(ARS_IOT_LOG_NAME); if (log) { SPDLOG_LOGGER_CRITICAL(spdlog::get(ARS_IOT_LOG_NAME), __VA_ARGS__); }; 0;}) 

// #define ARSIOT_DEBUG(...) SPDLOG_LOGGER_DEBUG(spdlog::get(ARS_IOT_LOG_NAME), __VA_ARGS__)
// #define ARSIOT_INFO(...) SPDLOG_LOGGER_INFO(spdlog::get(ARS_IOT_LOG_NAME), __VA_ARGS__)
// #define ARSIOT_WARN(...) SPDLOG_LOGGER_WARN(spdlog::get(ARS_IOT_LOG_NAME), __VA_ARGS__)
// #define ARSIOT_ERROR(...) SPDLOG_LOGGER_ERROR(spdlog::get(ARS_IOT_LOG_NAME), __VA_ARGS__)
// #define ARSIOT_CRITICAL(...) SPDLOG_LOGGER_CRITICAL(spdlog::get(ARS_IOT_LOG_NAME), __VA_ARGS__)

/**
 * @brief 日志等级
 * 
 */
enum ars_iot_log_level {
	log_trace = spdlog::level::trace,
    log_debug = spdlog::level::debug,
    log_info = spdlog::level::info,
    log_warn = spdlog::level::warn,
    log_err = spdlog::level::err,
    log_critical = spdlog::level::critical,
    log_off = spdlog::level::off,
    log_n_levels
};

/**
 * @brief Get the log default path object
 * 
 * @return std::string 
 */
std::string get_log_default_path(void);

/**
 * @brief 设置日志
 * @todo:如何调整输入到控制台、文件
 * 
 * @param log_name 日志模块名称，必须要填
 * @param level 日志等级，当设置已有日志时，将修改日志等级
 * @param filename 日志文件名称，如果是空的，则只是输出到控制台
 * @param max_file_size 文件最大大小
 * @param max_files 最大文件数量
 */
void set_logger(const char *log_name, ars_iot_log_level level, const char *filename, size_t max_file_size, size_t max_files);

///< 简单注册
inline void set_logger(const char *log_name) {
	ars::iot::set_logger(log_name, ars::iot::log_trace, get_log_default_path().c_str(), ARS_IOT_LOG_FILE_MAX_SIZE, ARS_IOT_LOG_FILE_MAX_NUM);
}

///< 指定等级
inline void set_logger(const char *log_name, ars_iot_log_level level) {
	ars::iot::set_logger(log_name, level, get_log_default_path().c_str(), ARS_IOT_LOG_FILE_MAX_SIZE, ARS_IOT_LOG_FILE_MAX_NUM);
}

///< 指定文件名
inline void set_logger(const char *log_name, ars_iot_log_level level, const char *filename) {
	ars::iot::set_logger(log_name, level, filename, ARS_IOT_LOG_FILE_MAX_SIZE, ARS_IOT_LOG_FILE_MAX_NUM);
}

inline void release_logger(void) {
	spdlog::shutdown();
}
// TODO:删除日志

} // namespace iot

} // namespace ars
