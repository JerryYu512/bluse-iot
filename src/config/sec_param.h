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
 * @file sec_param.h
 * @brief 加密参数
 * @author Jerry.Yu (jerry.yu512outlook.com)
 * @version 1.0.0
 * @date 2022-04-03
 * 
 * @copyright MIT License
 * 
 */
#pragma once
#include <stdint.h>
#include "basic/defs/ds.h"

namespace biot {

/// 加密信息最长4kb
#define MAX_SEC_INFO_LEN (4*1024)

/**
 * @brief 设备加密信息
 * 
 */
typedef struct sec_param_s {
	bin_data_header_t header;	///< 头部
	uint32_t devtype;			///< 设备类型
	uint32_t language;			///< 语言
	uint32_t sec_version;		///< 版本
	uint32_t device_class;		///< 产品类别
	uint32_t custom_len;		///< 扩展信息长度，为0时无扩展信息
	uint32_t oem;				///< oem，为1时有效
	uint8_t product_date[16];	///< 生产日期
	uint8_t product_update[16];	///< 产品固件更新日期，一般是维修/重新加密用
	uint8_t product_no[16];		///< 设备序列号
	uint8_t product_model[64];	///< 产品型号
	uint8_t mac[16][6];			///< mac地址
	uint8_t res[128];			///< 预留
} sec_param_t;

} // namespace biot
