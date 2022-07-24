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
 * @file capa_hardware.h
 * @brief 
 * @author Jerry.Yu (jerry.yu512outlook.com)
 * @version 1.0.0
 * @date 2022-04-03
 * 
 * @copyright MIT License
 * 
 */
#pragma once
#include <stdint.h>
#include <string>
#include "config/param/param_def/enums/e_hw.pm.h"
#include "config/param/param_def/enums/e_network.pm.h"

namespace biot {

/**
 * @brief 硬件能力
 * 
 */
typedef struct capa_hardware_s {
	uint32_t hw_version;	///< 硬件版本
	std::string device_model;	///< 设备型号
	uint64_t flash_size;	///< flash大小
	uint64_t ram_size;		///< 内存大小
	uint8_t cpu_num;		///< cpu个数
	uint8_t rj45_num;		///< rj45网口个数
	uint8_t usb_num;		///< usb个数
	uint8_t typec_num;		///< typec个数
	uint8_t hdmi_num;		///< hdmi个数
	uint8_t uart_num;		///< uart个数
	uint8_t i2c_num;		///< i2c个数
	uint8_t vga_num;		///< vga个数
	uint8_t sd_num;			///< sd卡个数
	bool support_wifi;		///< 支持wifi
	bool support_ppp;		///< 支持拨号
	bool support_video_out;	///< 支持视频输出
	NetIfRate netrate;		///< 网口速率
	bool support_emmc;		///< 是否支持emmc
	bool support_nand;		///< 是否支持nand
	bool support_bluetooth;	///< 支持蓝牙
	bool support_gps;		///< 支持gps
	bool support_led;		///< 支持led
	bool support_lcd;		///< 支持lcd
} capa_hardware_t;

} // namespace biot
