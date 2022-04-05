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
 * @file boot.cpp
 * @brief 
 * @author wotsen (astralrovers@outlook.com)
 * @version 1.0.0
 * @date 2021-08-15
 * 
 * @copyright MIT License
 * 
 */
#include "boot.h"
#include "basic/log/biot_log.h"
#include <list>

namespace biot {

static std::list<boot_t> ready_boots;

int biot_boot(std::vector<boot_t>& boots) {
	for (auto &b: boots) {
		int ret = BOOT_NONE;
        biot_boot_printi("booting [%s]\n", b.name.c_str());
		if (b.boot) {
			ret = b.boot();
			if (BOOT_OK == ret) {
        		biot_boot_printi("boot success [%s]\n", b.name.c_str());
				ready_boots.push_front(b);
			} else if (BOOT_FAILD == ret) {
        		biot_boot_printe("boot failed [%s]\n", b.name.c_str());
			} else if (BOOT_REBOOT == ret) {
        		biot_boot_printe("boot fatal [%s]\n", b.name.c_str());
        		biot_boot_printe("release all ready boot\n");
				for (auto &r: ready_boots) {
					if (r.release) {
						r.release();
					}
				}
				ready_boots.clear();
        		biot_boot_printe("reboot by [%s]\n", b.name.c_str());
				// 重启要求，直接返回
				return ret;
			} else {
        		biot_boot_printi("boot not need [%s]\n", b.name.c_str());
			}
		}

		b.result = ret;
	}
	
	return 0;
}

} // namespace biot
