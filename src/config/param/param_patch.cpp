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
 * @file param_patch.cpp
 * @brief 
 * @author Jerry.Yu (jerry.yu512outlook.com)
 * @version 1.0.0
 * @date 2022-05-16
 * 
 * @copyright MIT License
 * 
 */
#include <vector>
#include "param_patch/patch_product.h"
#include "param_patch.h"

namespace biot {

// 产品列表补丁
static struct app_param_product_patch_table product_table[] = {
	{0x0, product_patch_example, nullptr},
};

int patch_for_product(int device_type) {
	int ret = 0;
	for (auto &item : product_table) {
		bool match = false;
		if (item.match) {
			if (item.match(item.device_type)) {
				match = true;
			}
		} else if (device_type == item.device_type) {
			match = true;
		}
		// 匹配上才打补丁
		if (match && item.patch) {
			ret = item.patch(app_param_header(), app_param());
		}
		break;
	}

	return ret;
}

} // namespace biot
