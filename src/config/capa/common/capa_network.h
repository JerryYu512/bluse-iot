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
 * @file capa_network.h
 * @brief 网络能力级
 * @author Jerry.Yu (jerry.yu512outlook.com)
 * @version 1.0.0
 * @date 2022-04-03
 * 
 * @copyright MIT License
 * 
 */
#pragma once
#include <vector>
#include <string>
#include "basic/defs/ds.h"
#include "basic/defs/enum_def.h"

namespace biot {

/**
 * @brief 有线网能力
 * 
 */
typedef struct capa_lan_s {
	MaxMin<uint32_t> mtu_range;		///< mtu值
	LanWorkMode work_mode;			///< 网卡工作模式
	bool ipv6;						///< 支持ipv6
} capa_lan_t;

/**
 * @brief 无线网能力
 * 
 */
typedef struct capa_wireless_s {
	WireLessIfMode if_mode;			///< 网络接口模式
	WireLessWorkMode work_mode;		///< 无线工作模式
	WireLessSecMode security;		///< 安全模式
	WireLessWepAuthType wep_auth_type;	///< WEP认证类型
	WireLessWepKeyLen wep_key_len;		///< WEP密钥长度
	WireLessWepKeyType wep_key_type;	///< WEP密钥类型
	uint32_t wep_key_count;				///< WEP最大密钥数
	MaxMin<uint32_t> wpa_key_len_range;			///< WPA密钥长度范围
	WireLessWpaEncryptType wpa_encrypt_type;	///< WPA加密类型
} capa_wireless_t;

/**
 * @brief 拨号能力
 * 
 */
typedef struct capa_sim_s {
	uint32_t sim_type;	///< 2G,3G,4G,5G
} capa_sim_t;

/**
 * @brief 网络能力
 * 
 */
typedef struct capa_network_s {
	capa_lan_t lan;				///< 有线网能力
	capa_wireless_t wireless;	///< 无线网能力
	capa_sim_t	sim_card;		///< 拨号网能力
} capa_network_t;

} // namespace biot
