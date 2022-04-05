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
 * @file biot_log.h
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
// #define SPDLOG_HEADER_ONLY

#include <stdio.h>
#include <memory>
#include "spdlog/spdlog.h"
#include "spdlog/logger.h"
#include "biot_log_map.h"

// 日志根名称
#define BIOT_LOG_DEF_NAME "biot"
#define BIOT_DEF_LOG_FILENAME "biot.log"

// 模块索引
#ifndef BIOT_LOG_INDEX
#define BIOT_LOG_INDEX BIOT_LOG_DEFAULT
#endif

namespace biot {

/**
 * @brief 日志等级
 * 
 */
enum biot_log_level {
	log_trace = spdlog::level::trace,
    log_debug = spdlog::level::debug,
    log_info = spdlog::level::info,
    log_warn = spdlog::level::warn,
    log_err = spdlog::level::err,
    log_critical = spdlog::level::critical,
    log_off = spdlog::level::off,
    log_n_levels
};

// 默认日志等级
#ifdef DEBUG
#define BIOT_LOG_LEVEL_DEF biot::log_debug
#else
#define BIOT_LOG_LEVEL_DEF biot::log_info
#endif

// 输出方法
// 不输出到任何位置
#define BIOT_LOG_METHOD_NONE (0)
// 输出到终端
#define BIOT_LOG_METHOD_CONSOLE (1 << 0)
// 输出到文件
#define BIOT_LOG_METHOD_FILE (1 << 1)
// 输出到graylog日志收集平台
#define BIOT_LOG_METHOD_GRAYLOG (1 << 2)

// 默认输出方法
#define BIOT_LOG_METHOD_DEF BIOT_LOG_METHOD_CONSOLE

// 启动时的打印接口
#ifdef DEBUG
#define biot_boot_printd(fmt, ...) \
    printf("[BOOT][DEBUG][%s:%d:%s]" fmt, __FILE__, __LINE__, __func__, ##__VA_ARGS__)
#define biot_boot_verbose() printf("xxxxxx %s:%s:%d xxxxxx\n", __FILE__, __func__, __LINE__)
#else
#define biot_boot_printd(...)
#define biot_boot_verbose()
#endif

#define biot_boot_printi(fmt, ...) \
    printf("[BOOT][INFO][%s:%d:%s]" fmt, __FILE__, __LINE__, __func__, ##__VA_ARGS__)
#define biot_boot_printe(fmt, ...) \
    printf("[BOOT][ERROR][%s:%d:%s]" fmt, __FILE__, __LINE__, __func__, ##__VA_ARGS__)

// 运行时日志接口
#define BIOT_TRACE(...) ({auto log = biot::get_logger(BIOT_LOG_INDEX); auto lv = biot::get_log_level(BIOT_LOG_INDEX); if (log && lv >= biot::log_trace) { SPDLOG_LOGGER_TRACE(log, __VA_ARGS__); }; 0;}) 
#define BIOT_DEBUG(...) ({auto log = biot::get_logger(BIOT_LOG_INDEX); auto lv = biot::get_log_level(BIOT_LOG_INDEX); if (log && lv >= biot::log_debug) { SPDLOG_LOGGER_DEBUG(log, __VA_ARGS__); }; 0;}) 
#define BIOT_INFO(...) ({auto log = biot::get_logger(BIOT_LOG_INDEX); auto lv = biot::get_log_level(BIOT_LOG_INDEX); if (log && lv >= biot::log_info) { SPDLOG_LOGGER_INFO(log, __VA_ARGS__); }; 0;}) 
#define BIOT_WARN(...) ({auto log = biot::get_logger(BIOT_LOG_INDEX); auto lv = biot::get_log_level(BIOT_LOG_INDEX); if (log && lv >= biot::log_warn) { SPDLOG_LOGGER_WARN(log, __VA_ARGS__); }; 0;}) 
#define BIOT_ERROR(...) ({auto log = biot::get_logger(BIOT_LOG_INDEX); auto lv = biot::get_log_level(BIOT_LOG_INDEX); if (log && lv >= biot::log_err) { SPDLOG_LOGGER_ERROR(log, __VA_ARGS__); }; 0;}) 
#define BIOT_CRITICAL(...) ({auto log = biot::get_logger(BIOT_LOG_INDEX); auto lv = biot::get_log_level(BIOT_LOG_INDEX); if (log && lv >= biot::log_critical) { SPDLOG_LOGGER_CRITICAL(log, __VA_ARGS__); }; 0;}) 

/**
 * @brief 日志初始化
 * 
 */
void init_log(void);

/**
 * @brief 设置日志等级
 * 
 * @param log_idx 
 * @param level 
 */
void set_log_level(int log_idx, biot_log_level level);

/**
 * @brief 获取日志等级
 * 
 * @param idx 模块索引
 * @return biot_log_level 
 */
biot_log_level get_log_level(int idx);

/**
 * @brief 获取日志句柄
 * 
 * @param idx 模块索引
 * @return std::shared_ptr<spdlog::logger> 
 */
std::shared_ptr<spdlog::logger> get_logger(int idx);

} // namespace biot
