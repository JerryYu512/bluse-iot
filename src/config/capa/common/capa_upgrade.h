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
 * @file capa_upgrade.h
 * @brief 升级能力
 * @author Jerry.Yu (jerry.yu512outlook.com)
 * @version 1.0.0
 * @date 2022-04-03
 * 
 * @copyright MIT License
 * 
 */
#pragma once
#include <string>
#include "basic/defs/ds.h"

namespace biot {

/// 统一升级标记
#define UNI_UPGRADE_TAG "bluse.io/IOT/021"

/**
 * @brief 升级能力
 * 
 */
typedef struct capa_upgrade_s {
	std::string uni_upgrade_tag;	///< 统一升级标记
	uint32_t plarform;				///< 平台
	uint32_t language;				///< 语言
	uint32_t major_type;			///< 主类型
	uint32_t minor_type;			///< 次类型
	std::string package_fmt;		///< 升级包格式
	MaxMin<uint32_t> softversion_range;	///< 支持升级的本版号范围，最小位0，则支持完全向下升级，最大为0，则支持完全向上升级
} capa_upgrade_t;

} // namespace biot
