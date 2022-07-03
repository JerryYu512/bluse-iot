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
 * @file patch_product_example.cpp
 * @brief 
 * @author Jerry.Yu (jerry.yu512outlook.com)
 * @version 1.0.0
 * @date 2022-05-16
 * 
 * @copyright MIT License
 * 
 */
#include "patch_product.h"
#include "../param_patch.h"

namespace biot {
	
// 实际补丁接口
static int patch_20220501(app_param_check_t &header, BiotAppParam &param);

// 补丁列表，和参数版本对应
static struct app_param_patch_table patch_table[] = {
	{20220501, patch_20220501},
};

static int patch_20220501(app_param_check_t &header, BiotAppParam &param) {
	// TODO:
	return 0;
}

// 示例补丁产品
int product_patch_example(app_param_check_t &header, BiotAppParam &param) {
	uint32_t lastversion = 0;
	for (auto &item : patch_table) {
		if (item.param_version > header.storage_version) {
			item.patch(header, param);
			header.storage_version = item.param_version;
		}
		lastversion = item.param_version;
	}
	// 更新到最终的参数版本
	header.storage_version = lastversion;

	return 0;
}

} // namespace biot
