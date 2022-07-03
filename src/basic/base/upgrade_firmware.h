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
 * @file upgrade_firmware.h
 * @brief 升级定义头文件
 * @author Jerry.Yu (jerry.yu512outlook.com)
 * @version 1.0.0
 * @date 2022-05-15
 * 
 * @copyright MIT License
 * 
 */
#pragma once
#include <stdint.h>

namespace biot {

enum BIOT_SOFTWARE_ATTR: uint8_t {
	E_BIOT_SW_DEBUG,
	E_BIOT_SW_STANDARD,
	E_BIOT_SW_NEUTRAL,
};

enum BIOT_PRIOD_VERSION: uint8_t {
	E_BIOT_PRIOD_BASE,
	E_BIOT_PRIOD_ALPHA,
	E_BIOT_PRIOD_BETA,
	E_BIOT_PRIOD_RC,
	E_BIOT_PRIOD_RELEASE,
};

// 升级状态
enum BIOT_UPGRADE_STATE {
	E_BIOT_UP_IDLE,				// 空闲，待升级
	E_BIOT_UP_START,			// 开始升级
	E_BIOT_UP_DOWNLOADING,		// 下载中
	E_BIOT_UP_DOWNLOAD_COMPLATE,	// 下载成功
	E_BIOT_UP_CHECKING,			// 校验中
	E_BIOT_UP_DOING,			// 升级中
	E_BIOT_UP_SUCCESS,			// 升级成功
	E_BIOT_UP_FAILED,			// 升级失败
	E_BIOT_UP_RESTARTING,		// 重启中
};

// 单个模块升级包
typedef struct {
	char name[128];		///< 资源包名称
	uint32_t version;	///< 升级包版本
	uint32_t date;		///< 升级包日期
	char hash[256];		///< 升级包摘要
	uint32_t size;		///< 升级包大小
} upgrade_single_file_t;

// 升级包包头
typedef struct {
	uint32_t magic;			///< 魔术字'B' 'T' 'U' 'P'
	uint32_t base_verison;	///< 固件版本
	uint32_t package_type;	///< 包类型，1是全量包，2-0xfffffffe为应用模块升级包
	uint32_t device_class;	///< 设备类型
	uint32_t platform;		///< 平台
	uint32_t language;		///< 语言
	uint8_t attribute;		///< 属性,debug,standard,neutral
	uint16_t up_version;	///< 升级协议版本
	uint8_t priod_version;	///< 阶段版本base,alpha,beta,rc,release
	uint32_t version;		///< 软件包版本
	uint32_t date;			///< 日期
	uint32_t custom;		///< 客户码
	char res[64];
	char hash[256];			///< 升级包摘要，package_num之后的内容
	uint32_t package_num;	///< 升级资源包数量
} upgrade_file_header_t;

} // namespace biot
