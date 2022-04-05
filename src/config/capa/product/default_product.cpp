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
 * @file default_product.cpp
 * @brief 
 * @author Jerry.Yu (jerry.yu512outlook.com)
 * @version 1.0.0
 * @date 2022-04-03
 * 
 * @copyright MIT License
 * 
 */
#include "../capa.h"

namespace biot {

void capa_patch_default_product(device_capa_t& capa);

static void capa_patch_hw(capa_hardware_t& capa_hw);
static void capa_patch_sw(capa_software_t& capa_sw);
static void capa_patch_net(capa_network_t& capa_net);
static void capa_patch_up(capa_upgrade_t& capa_up);
	
static void capa_patch_hw(capa_hardware_t& capa_hw)
{

}

static void capa_patch_sw(capa_software_t& capa_sw)
{

}

static void capa_patch_net(capa_network_t& capa_net)
{

}

static void capa_patch_up(capa_upgrade_t& capa_up)
{

}
	
void capa_patch_default_product(device_capa_t& capa)
{
	capa_patch_hw(capa.capa_hw);
	capa_patch_sw(capa.capa_sw);
	capa_patch_net(capa.capa_net);
	capa_patch_up(capa.capa_up);
}

} // namespace biot
