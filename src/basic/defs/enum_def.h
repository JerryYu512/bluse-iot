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
 * @file enum_def.h
 * @brief 枚举定义
 * @author Jerry.Yu (jerry.yu512outlook.com)
 * @version 1.0.0
 * @date 2022-04-03
 * 
 * @copyright MIT License
 * 
 */
#pragma once

namespace biot {

#define EBIT(n) (1 << (n))

/**
 * @brief 可选运行模式
 * 
 */
enum AppMode {
	APP_DEVICE_MODE		= 0,		///< 设备模式
	APP_GATEWAY_MODE	= EBIT(0),	///< 网关模式
	APP_DEV_GW_MODE		= EBIT(1),	///< 设备/网关模式
};

/**
 * @brief 有线网工作模式
 * 
 */
enum LanWorkMode {
	LAN_WORK_10M_HALF 	= 0,			///< 10M半双工
	LAN_WORK_10M_FULL 	= EBIT(0),		///< 10M全双工
	LAN_WORK_100M_HALF 	= EBIT(1),		///< 100M半双工
	LAN_WORK_100M_FULL 	= EBIT(2),		///< 100M全双工
	LAN_WORK_AUTO 		= EBIT(3),		///< 自适应
	LAN_WORK_1G_FULL 	= EBIT(4),		///< 1G全双工
};

/**
 * @brief 网口速率
 * 
 */
enum NetIfRate {
	NET_IF_RATE_100M,	///< 百兆网口
	NET_IF_RATE_1000M,	///< 千兆网口
};

/**
 * @brief 无线网网络接口模式
 * 
 */
enum WireLessIfMode {
	WIRELESS_IF_AUTO 	= 0,		///< 自动切换
	WIRELESS_IF_LAN 	= EBIT(0),	///< 有线模式
};

/**
 * @brief 无线工作模式
 * 
 */
enum WireLessWorkMode {
	WIRELESS_WORK_MANAGED 	= 0,
	WIRELESS_WORK_AD_HOC 	= EBIT(0),
};

/**
 * @brief 无线安全模式
 * 
 */
enum WireLessSecMode {
	WIRELESS_SEC_NONE 				= 0,		///< 不加密
	WIRELESS_SEC_WEP 				= EBIT(0),	///< WEP
	WIRELESS_SEC_WPA_PSK 			= EBIT(1),	///< WPA-PSK
	WIRELESS_SEC_WPA_ENTERPRISE		= EBIT(2),	///< WPA-enterprise
	WIRELESS_SEC_WPA2_PSK 			= EBIT(3),	///< WPA2-PSK
};

/**
 * @brief WEP认证类型
 * 
 */
enum WireLessWepAuthType {
	WIRELESS_WEPAUTH_OPEN	= 0,		///< 开放式
	WIRELESS_WEPAUTH_SHARE	= EBIT(0),	///< 共享式
};

/**
 * @brief WEP密钥长度
 * 
 */
enum WireLessWepKeyLen {
	WIRELESS_WEPKEY_LEN64	= 0,		///< 64位
	WIRELESS_WEPKEY_LEN128	= EBIT(0),	///< 128位
	WIRELESS_WEPKEY_LEN152	= EBIT(1),	///< 152位
};

/**
 * @brief WEP密钥类型
 * 
 */
enum WireLessWepKeyType {
	WIRELESS_WEPKEY_HEX 	= 0,		///< 16进制
	WIRELESS_WEPKEY_ASCII 	= EBIT(0),	///< ASCII码
};

/**
 * @brief WPA加密类型
 * 
 */
enum WireLessWpaEncryptType {
	WIRELESS_WPA_ENCRYPT_AES 	= 0,		///< AES
	WIRELESS_WPA_ENCRYPT_TKIP 	= EBIT(0),	///< TKIP
};

} // namespace biot
