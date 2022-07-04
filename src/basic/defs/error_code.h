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

// 通用错误码2-0xffff
enum CommonErrorCode: biot_err_t {
	BIOT_COMMON_ECODE_OK = 0,
	// 文件
	BIOT_COMMON_ECODE_FILE_NOT_EXIST = 2,		// 文件不存在
	BIOT_COMMON_ECODE_FILE_OPEN_FAILED,			// 文件打开失败
	BIOT_COMMON_ECODE_FILE_WRITE_FAILED,		// 文件写入失败
	BIOT_COMMON_ECODE_FILE_READ_FAILED,			// 文件读取失败

	// 内存
	BIOT_COMMON_ECODE_MEM_ALLOC_FAILED,			// 内存分配失败
	BIOT_COMMON_ECODE_MEM_INVALID,				// 内存不可用

	// 数据
	BIOT_COMMON_ECODE_DATA_JSON_TO_STRUCT_ERROR,	// json转结构体失败
	BIOT_COMMON_ECODE_DATA_STRUCT_TO_JSON_ERROR,	// 结构体转json失败

	// 无效值
	BIOT_COMMON_ECODE_MAX = 0xffff,
};

// 系统错误码
enum SystemErrorCode: biot_err_t {
	BIOT_SYS_ECODE_OK = 0,
	#define BECODE_SYS(code) BIOT_BASE_ECODE_SYSTEM | (code)
	
	/// 配置文件
	#define BECODE_SYS_CFGFILE(code) BECODE_SYS(0x0001 | (code))
	BIOT_SYS_ECODE_CFG_FILE_NOT_EXIST = BECODE_SYS_CFGFILE(0x0001),				// 配置文件不存在[str:app param config file not exist]
	BIOT_SYS_ECODE_CFG_FILE_OPEN_FAILED = BECODE_SYS_CFGFILE(0x0002),			// 配置文件不存在[str:app param config file not exist]
	BIOT_SYS_ECODE_CFG_FILE_HEADER_ERROR = BECODE_SYS_CFGFILE(0x0003),			// 配置文件不存在[str:app param config file not exist]
	BIOT_SYS_ECODE_CFG_FILE_HEADER_CHECK_FAILED = BECODE_SYS_CFGFILE(0x0004),	// 配置文件不存在[str:app param config file not exist]

	/// 升级
	#define BECODE_SYS_UP(code) BECODE_SYS(0x0002 | (code))
	BIOT_SYS_ECODE_UP_FILESIZE_MISMATCH = BECODE_SYS_UP(0x0001),			// 升级文件大小不匹配
	BIOT_SYS_ECODE_UP_FILESIZE_OVERSIZE = BECODE_SYS_UP(0x0002),			// 升级文件大小过大
	BIOT_SYS_ECODE_UP_DOMAIN_RESOLUTION_FAILED = BECODE_SYS_UP(0x0003),		// 升级文件下载地址异常
	BIOT_SYS_ECODE_UP_DOWNLOAD_TIMEOUT = BECODE_SYS_UP(0x0004),				// 升级文件下载超时
	BIOT_SYS_ECODE_UP_HASH_MISMATCH = BECODE_SYS_UP(0x0005),				// 升级文件摘要不匹配
	BIOT_SYS_ECODE_UP_SIGNATURE_CHECK_FAILED = BECODE_SYS_UP(0x0006),		// 升级文件验签失败
	BIOT_SYS_ECODE_UP_PACKAGE_ERROR = BECODE_SYS_UP(0x0007),				// 升级包损坏
	BIOT_SYS_ECODE_UP_PACKAGE_MEMORY_NOT_ENOUGH = BECODE_SYS_UP(0x0008),	// 内存不足
	BIOT_SYS_ECODE_UP_WRITE_FAILED = BECODE_SYS_UP(0x0009),					// 烧录失败
	BIOT_SYS_ECODE_UP_USER_STOP = BECODE_SYS_UP(0x000a),					// 用户停止升级
	BIOT_SYS_ECODE_UP_DOING = BECODE_SYS_UP(0x000b),						// 正在升级
	BIOT_SYS_ECODE_UP_UNKNOWN = BECODE_SYS_UP(0x000c),						// 底层接口错误
	BIOT_SYS_ECODE_UP_SOFT_VERSION_NOT_PERMISSION = BECODE_SYS_UP(0x000d),	// 版本不允许升级
	BIOT_SYS_ECODE_UP_PLATFORM_MISMATCH = BECODE_SYS_UP(0x000e),			// 平台不匹配
	BIOT_SYS_ECODE_UP_DEVICE_MISMATCH = BECODE_SYS_UP(0x000f),				// 设备类型不匹配
	BIOT_SYS_ECODE_UP_LANGUAGE_MISMATCH = BECODE_SYS_UP(0x0010),			// 语言不匹配
	BIOT_SYS_ECODE_UP_VERSION_NOT_SUPPORT = BECODE_SYS_UP(0x0011),			// 升级协议不兼容
};

} // namespace biot
