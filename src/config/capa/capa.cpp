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
 * @file capa.cpp
 * @brief 
 * @author Jerry.Yu (jerry.yu512outlook.com)
 * @version 1.0.0
 * @date 2022-04-03
 * 
 * @copyright MIT License
 * 
 */
#include "capa.h"

namespace biot {

static device_capa_t device_capa;

const device_capa_t &capa_device(void)
{
	return device_capa;
}

const capa_hardware_t &capa_hw(void)
{
	return device_capa.capa_hw;
}

const capa_software_t &capa_sw(void)
{
	return device_capa.capa_sw;
}

const capa_network_t &capa_net(void)
{
	return device_capa.capa_net;
}

const capa_upgrade_t &capa_up(void)
{
	return device_capa.capa_up;
}

void capa_init(uint32_t devtype, const std::vector<capa_patch_product_t>& patchs)
{
	for (auto &item : patchs) {
		if (item.devtype == devtype) {
			if (item.patch) {
				item.patch(device_capa);
			} else {
				break;
			}
		}
	}

	return;
}

} // namespace biot
