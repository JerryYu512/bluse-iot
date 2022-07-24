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
 * @file error_code.h
 * @brief 
 * @author Jerry.Yu (jerry.yu512outlook.com)
 * @version 1.0.0
 * @date 2022-05-15
 * 
 * @copyright MIT License
 * 
 */
#pragma once
#include <stdint.h>
#include "app_module_id.h"

namespace biot {

typedef uint64_t biot_err_t;

#define BIOT_OK 0

// 基础领域错误码为64位/8字节，0xffffffff
// 1-2字节为每个模块的具体错误码
// 3-4字节为子模块编号
// 5字节为主模块编号
// 6字节为错误标识
// 7-8字节为软件编号
// 0x0001 01 01 0001 0001
#define BIOT_MODULE_ECODE_START(id) (biot_err_t)(id) << 32
#define BIOT_MODULE_ID_FROM_ECODE(code) (((biot_err_t)(code) >> 32) & 0xff)
enum BaseErrorDomain: biot_err_t {
	BIOT_BASE_OK = BIOT_OK,					// 成功[str:ok]
	BIOT_BASE_ECODE_COMMON = 0x0001,		// 通用错误码起始[str:common res]
	BIOT_BASE_ECODE_SYSTEM = BIOT_MODULE_ECODE_START(E_BIOT_MODULE_SYSTEM_ID),		// 系统错误码起始[str:system]
	BIOT_BASE_ECODE_SUBSYS = BIOT_MODULE_ECODE_START(E_BIOT_MODULE_SUB_SYSTEM_ID),	// 子系统错误码起始[str:sub system]
	BIOT_BASE_ECODE_THIRD = BIOT_MODULE_ECODE_START(E_BIOT_MODULE_THIRDPARTY_ID),	// 依赖库错误码起始[str:thirdparty]
	BIOT_BASE_ECODE_ALGO = BIOT_MODULE_ECODE_START(E_BIOT_MODULE_ALGO_ID),			// 算法错误码起始[str:algo]
	BIOT_BASE_ECODE_DB = BIOT_MODULE_ECODE_START(E_BIOT_MODULE_DB_ID),				// 数据库错误码起始[str:database]
	BIOT_BASE_ECODE_HW = BIOT_MODULE_ECODE_START(E_BIOT_MODULE_HW_ID),				// 硬件错误码起始[str:hardware]
	BIOT_BASE_ECODE_DEV = BIOT_MODULE_ECODE_START(E_BIOT_MODULE_DEVICE_ID),			// 设备错误码起始[str:device]
	BIOT_BASE_ECODE_MEDIA = BIOT_MODULE_ECODE_START(E_BIOT_MODULE_MEDIA_ID),		// 媒体错误码起始[str:media]
	BIOT_BASE_ECODE_NET = BIOT_MODULE_ECODE_START(E_BIOT_MODULE_NET_ID),			// 网络错误码起始[str:network]
	BIOT_BASE_ECODE_STORAGE = BIOT_MODULE_ECODE_START(E_BIOT_MODULE_STORAGE_ID),	// 存储错误码起始[str:storage]
	BIOT_BASE_UNKNOWN = 0xffffffff,			// 未知[str:unknown]
};

#define BECODE_SYS(code) BIOT_BASE_ECODE_SYSTEM | (code)
// 系统-配置文件错误起始码
#define BECODE_SYS_CFGFILE(code) BECODE_SYS(0x0001 | (code))
// 系统-升级错误起始码
#define BECODE_SYS_UP(code) BECODE_SYS(0x10001 | (code))

// 错误码
#define BIOT_ERROR_CODE_MAP(XX) \
	XX(BIOT_ECODE_OK = BIOT_OK, BIOT_ECODE_OK, "success", "成功") \
	/* 通用错误码2-0xffff */ \
	/* 文件 */ \
	XX(BIOT_COMMON_ECODE_FILE_NOT_EXIST = 2, BIOT_COMMON_ECODE_FILE_NOT_EXIST, "file not exist", "文件不存在") \
	XX(BIOT_COMMON_ECODE_FILE_OPEN_FAILED, BIOT_COMMON_ECODE_FILE_OPEN_FAILED, "file wopen failed", "文件打开失败") \
	XX(BIOT_COMMON_ECODE_FILE_WRITE_FAILED, BIOT_COMMON_ECODE_FILE_WRITE_FAILED, "file write error", "文件写入异常") \
	XX(BIOT_COMMON_ECODE_FILE_READ_FAILED, BIOT_COMMON_ECODE_FILE_READ_FAILED, "file read error", "文件读取异常") \
	/* 内存 */ \
	XX(BIOT_COMMON_ECODE_MEM_ALLOC_FAILED, BIOT_COMMON_ECODE_MEM_ALLOC_FAILED, "memory alloc failed", "内存分配失败") \
	XX(BIOT_COMMON_ECODE_MEM_INVALID, BIOT_COMMON_ECODE_MEM_INVALID, "memory invalid", "内存不可用") \
	/* 数据 */ \
	XX(BIOT_COMMON_ECODE_DATA_JSON_FMT_ERROR, BIOT_COMMON_ECODE_DATA_JSON_FMT_ERROR, "json format error", "json格式错误") \
	XX(BIOT_COMMON_ECODE_DATA_JSON_TO_STRUCT_ERROR, BIOT_COMMON_ECODE_DATA_JSON_TO_STRUCT_ERROR, "json trans to struct failed", "json转结构体错误") \
	XX(BIOT_COMMON_ECODE_DATA_STRUCT_TO_JSON_ERROR, BIOT_COMMON_ECODE_DATA_STRUCT_TO_JSON_ERROR, "struct trans to json failed", "结构体转json错误") \
	XX(BIOT_COMMON_ECODE_DATA_OVER_MAX, BIOT_COMMON_ECODE_DATA_OVER_MAX, "data over max", "数据大于最大值") \
	XX(BIOT_COMMON_ECODE_DATA_OVER_MIN, BIOT_COMMON_ECODE_DATA_OVER_MIN, "data over min", "数据小于最小值") \
	XX(BIOT_COMMON_ECODE_DATA_NOT_IN_RANGE, BIOT_COMMON_ECODE_DATA_NOT_IN_RANGE, "data not in range", "数据不在范围内") \
	/* 流程 */ \
	/* 无效值 */ \
	XX(BIOT_COMMON_ECODE_MAX = 0xffff, BIOT_COMMON_ECODE_MAX, "invalid common code", "无效的通用错误码") \
	/* 系统错误码0x10000-0x1ffff */ \
	/* 配置文件 */ \
	XX(BIOT_SYS_ECODE_CFG_FILE_NOT_EXIST = BECODE_SYS_CFGFILE(0x0001), BIOT_SYS_ECODE_CFG_FILE_NOT_EXIST, "configure file not exist", "配置文件不存在") \
	XX(BIOT_SYS_ECODE_CFG_FILE_OPEN_FAILED, BIOT_SYS_ECODE_CFG_FILE_OPEN_FAILED, "configure file open error", "配置文件打开错误") \
	XX(BIOT_SYS_ECODE_CFG_FILE_HEADER_ERROR, BIOT_SYS_ECODE_CFG_FILE_HEADER_ERROR, "configure file header error", "配置文件头错误") \
	XX(BIOT_SYS_ECODE_CFG_FILE_HEADER_CHECK_FAILED, BIOT_SYS_ECODE_CFG_FILE_HEADER_CHECK_FAILED, "configure file header check error", "配置文件头校验失败") \
	/* 升级 */ \
	XX(BIOT_SYS_ECODE_UP_FILESIZE_MISMATCH = BECODE_SYS_UP(0x0001), BIOT_SYS_ECODE_UP_FILESIZE_MISMATCH, "Upgrade file size mismatch", "升级文件大小不匹配") \
	XX(BIOT_SYS_ECODE_UP_FILESIZE_OVERSIZE, BIOT_SYS_ECODE_UP_FILESIZE_OVERSIZE, "The upgrade file size is too large", "升级文件大小过大") \
	XX(BIOT_SYS_ECODE_UP_DOMAIN_RESOLUTION_FAILED, BIOT_SYS_ECODE_UP_DOMAIN_RESOLUTION_FAILED, "The download address of the upgrade file is abnormal", "升级文件下载地址异常") \
	XX(BIOT_SYS_ECODE_UP_DOWNLOAD_TIMEOUT, BIOT_SYS_ECODE_UP_DOWNLOAD_TIMEOUT, "Upgrade file download timed out", "升级文件下载超时") \
	XX(BIOT_SYS_ECODE_UP_HASH_MISMATCH, BIOT_SYS_ECODE_UP_HASH_MISMATCH, "Upgrade file digests do not match", "升级文件摘要不匹配") \
	XX(BIOT_SYS_ECODE_UP_SIGNATURE_CHECK_FAILED, BIOT_SYS_ECODE_UP_SIGNATURE_CHECK_FAILED, "Upgrade file signature verification failed", "升级文件验签失败") \
	XX(BIOT_SYS_ECODE_UP_PACKAGE_ERROR, BIOT_SYS_ECODE_UP_PACKAGE_ERROR, "The upgrade package is corrupted", "升级文件包损坏") \
	XX(BIOT_SYS_ECODE_UP_PACKAGE_MEMORY_NOT_ENOUGH, BIOT_SYS_ECODE_UP_PACKAGE_MEMORY_NOT_ENOUGH, "Insufficient memory for upgrade", "升级内存不足") \
	XX(BIOT_SYS_ECODE_UP_WRITE_FAILED, BIOT_SYS_ECODE_UP_WRITE_FAILED, "Burning failed", "烧录失败") \
	XX(BIOT_SYS_ECODE_UP_USER_STOP, BIOT_SYS_ECODE_UP_USER_STOP, "User stops upgrading", "用户停止升级") \
	XX(BIOT_SYS_ECODE_UP_DOING, BIOT_SYS_ECODE_UP_DOING, "upgrading", "正在升级") \
	XX(BIOT_SYS_ECODE_UP_UNKNOWN, BIOT_SYS_ECODE_UP_UNKNOWN, "low-level interface error", "底层接口错误") \
	XX(BIOT_SYS_ECODE_UP_SOFT_VERSION_NOT_PERMISSION, BIOT_SYS_ECODE_UP_SOFT_VERSION_NOT_PERMISSION, "Version not allowed to upgrade", "版本不允许升级") \
	XX(BIOT_SYS_ECODE_UP_PLATFORM_MISMATCH, BIOT_SYS_ECODE_UP_PLATFORM_MISMATCH, "Platform mismatch", "平台不匹配") \
	XX(BIOT_SYS_ECODE_UP_DEVICE_MISMATCH, BIOT_SYS_ECODE_UP_DEVICE_MISMATCH, "Device type mismatch", "设备类型不匹配") \
	XX(BIOT_SYS_ECODE_UP_LANGUAGE_MISMATCH, BIOT_SYS_ECODE_UP_LANGUAGE_MISMATCH, "language mismatch", "语言不匹配") \
	XX(BIOT_SYS_ECODE_UP_VERSION_NOT_SUPPORT, BIOT_SYS_ECODE_UP_VERSION_NOT_SUPPORT, "Upgrade protocol is not compatible", "升级协议不兼容") \
	/* 子系统错误码0x20000-0x2ffff */ \
	/* 第三方库错误码0x30000-0x3ffff */ \
	/* 算法错误码0x30000-0x3ffff */ \
	/* 数据库错误码0x30000-0x3ffff */ \
	/* 硬件错误码0x30000-0x3ffff */ \
	/* 设备错误码0x30000-0x3ffff */ \
	/* 媒体错误码0x30000-0x3ffff */ \
	/* 网络错误码0x30000-0x3ffff */ \
	/* 存储错误码0x30000-0x3ffff */ \


// 错误码定义
typedef enum BiotErrorCodeE: biot_err_t {
#define BIOT_ERROR_CODE_MAP_TO_ENUM_DEF(expr, value, str, desc) expr,
	BIOT_ERROR_CODE_MAP(BIOT_ERROR_CODE_MAP_TO_ENUM_DEF)
#undef BIOT_ERROR_CODE_MAP_TO_ENUM_DEF
} BiotErrorCode;

/**
 * @brief 查询错误码，中文
 * 
 * @param no 
 * @return const char* 
 */
const char* query_error_code_zh(BiotErrorCode no);
static const char* query_error_code_zh(biot_err_t no) {
	return query_error_code_zh((BiotErrorCode)(no));
}

/**
 * @brief 查询错误码，英文
 * 
 * @param no 
 * @return const char* 
 */
const char* query_error_code_en(BiotErrorCode no);
const char* query_error_code_en(biot_err_t no) {
	return query_error_code_en((BiotErrorCode)(no));
}

/**
 * @brief 展示错误码
 * 
 */
void show_error_code(void);

} // namespace biot
