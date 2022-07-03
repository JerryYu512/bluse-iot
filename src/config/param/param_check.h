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
 * @file param_check.h
 * @brief 
 * @author Jerry.Yu (jerry.yu512outlook.com)
 * @version 1.0.0
 * @date 2022-04-03
 * 
 * @copyright MIT License
 * 
 */
#pragma once

#include "basic/defs/ds.h"

namespace biot {

// BCFG
#define BIOT_PARAM_FILE_MAGIC 0x42434647

/**
 * @brief 参数存储方式
 * 
 */
enum AppParamFileStorageType {
	APP_PARAM_FILE_STORAGE_BIN,
	APP_PARAM_FILE_STORAGE_JSON,
	APP_PARAM_FILE_STORAGE_INI,
	APP_PARAM_FILE_STORAGE_YAML,
	APP_PARAM_FILE_STORAGE_SQLITE3,

	APP_PARAM_FILE_STORAGE_MAX = UINT32_MAX
};

/**
 * @brief 存储来源
 * 
 */
enum AppParamFileStorageSource {
	APP_PARAM_FILE_STORAGE_BASELINE,
	APP_PARAM_FILE_STORAGE_CUSTOMIZE,

	APP_PARAM_FILE_STORAGE_MAX = UINT32_MAX
};

/**
 * @brief 参数存储校验信息
 * 
 */
typedef struct app_param_check_s {
	bin_data_header_t header;	///< 头部信息
	uint32_t storage_type;		///< 存储格式，用于解析
	uint16_t storage_source;	///< 存储来源
	uint16_t storage_version;	///< 存储版本
	uint64_t devtype;			///< 设备类型
	uint8_t update_time[32];	///< 修改日期
	uint8_t product_no[16];		///< 设备序列号，不做校验
	uint8_t uuid[64];			///< 唯一码，和正文中的该字段做比较
	uint8_t res[256];			///< 预留
	uint32_t custom_len;		///< 扩展长度
	uint32_t param_len;			///< 实际参数长度
} app_param_check_t;

} // namespace biot
