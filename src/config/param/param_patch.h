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
 * @file param_patch.h
 * @brief 
 * @author Jerry.Yu (jerry.yu512outlook.com)
 * @version 1.0.0
 * @date 2022-05-16
 * 
 * @copyright MIT License
 * 
 */
#pragma once
#include "param.h"

namespace biot {

typedef int (*app_param_patch_fn)(app_param_check_t &header, BiotAppParam &param);
typedef int (*app_param_product_patch_fn)(app_param_check_t &header, BiotAppParam &param);
// 用户自定义的匹配补丁接口
typedef bool (*product_match_fn)(int device_type);

struct app_param_product_patch_table {
	uint32_t device_type;					// 设备类型
	app_param_product_patch_fn patch;	// 产品补丁接口
	product_match_fn match;				// 产品匹配
};

struct app_param_patch_table {
	uint32_t param_version;			// 补丁版本号
	app_param_patch_fn patch;	// 补丁接口
};

/**
 * @brief 通用补丁
 * 
 * @return int 
 */
int patch_common(void);

/**
 * @brief 产品补丁
 * 
 * @param device_type 
 * @param match 
 */
int patch_for_product(int device_type);

} // namespace biot
