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
 * @file capa.h
 * @brief 能力级
 * @author Jerry.Yu (jerry.yu512outlook.com)
 * @version 1.0.0
 * @date 2022-04-03
 * 
 * @copyright MIT License
 * 
 */
#pragma once

#include <functional>
#include <vector>
#include "common/capa_software.h"
#include "common/capa_hardware.h"
#include "common/capa_network.h"
#include "common/capa_upgrade.h"

namespace biot {

/**
 * @brief 设备能力
 * 
 */
typedef struct device_capa_s {
	capa_hardware_t capa_hw;	///< 硬件能力
	capa_software_t	capa_sw;	///< 软件能力
	capa_network_t  capa_net;	///< 网络能力
	capa_upgrade_t	capa_up;	///< 升级能力
} device_capa_t;

/**
 * @brief 产品补丁
 * 
 */
typedef struct capa_patch_product_s {
	uint32_t devtype;							///< 设备型号
	std::function<void(device_capa_t&)> patch;	///< 补丁接口
} capa_patch_product_t;

/**
 * @brief 能力初始化
 * 
 * @param devtype 设备型号
 * @param patchs 补丁
 */
void capa_init(uint32_t devtype, const std::vector<capa_patch_product_t>& patchs);

/**
 * @brief 获取设备能力级
 * 
 * @return const device_capa_t& 
 */
const device_capa_t &capa_device(void);

/// 获取硬件能力
const capa_hardware_t &capa_hw(void);

/// 获取软件能力
const capa_software_t &capa_sw(void);

/// 获取网络能力
const capa_network_t &capa_net(void);

/// 获取升级能力
const capa_upgrade_t &capa_up(void);

} // namespace biot
