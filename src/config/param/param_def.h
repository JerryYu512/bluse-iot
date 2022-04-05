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
 * @file param_def.h
 * @brief 
 * @author Jerry.Yu (jerry.yu512outlook.com)
 * @version 1.0.0
 * @date 2022-04-03
 * 
 * @copyright MIT License
 * 
 */
#pragma once

#include "basic/defs/reflection.h"
#include "common/param_basic.h"
#include "common/param_module.h"
#include "common/param_sys.h"

namespace biot {

#include OATPP_CODEGEN_BEGIN(DTO)

// NTP
// Storage
// db
// hw-iot

class CfgWebService : public oatpp::DTO {
	DTO_INIT(CfgWebService, DTO)

	// http配置
	DTO_FIELD(Boolean, http_port) = 80;
	DTO_FIELD(Boolean, https) = false;
	DTO_FIELD(Boolean, https_port) = 443;
};

class CfgLan : public oatpp:: DTO {
	DTO_INIT(CfgLan, DTO)

	DTO_FIELD(String, type, "10M-half, 10M-full, ...");
	// 自动获取/手动配置
	DTO_FIELD(UInt8, cfg_type);
	DTO_FIELD(String, if_name);
	DTO_FIELD(String, mac);
	DTO_FIELD(String, ipv4);
	DTO_FIELD(String, ipv6);
	DTO_FIELD(String, submask);
	DTO_FIELD(String, gateway);
	DTO_FIELD(UInt32, mtu);
	DTO_FIELD(String, dns);
};

// 基本网络参数
class CfgNetworkParam : public oatpp::DTO {
	DTO_INIT(CfgNetworkParam, DTO)

	DTO_FIELD(Object<CfgWebService>, web_service);
};

class DeviceParameter : public oatpp::DTO {
	DTO_INIT(DeviceParameter, DTO)

	// 设备信息
	DTO_FIELD(String, uuid);
	DTO_FIELD(String, exec_id);
	// 配置参数版本号
	DTO_FIELD(UInt32, version);
	// 设备可配置信息
	DTO_FIELD(String, device_name) = "biot 01";
	DTO_FIELD(String, device_id) = "1";
};

#include OATPP_CODEGEN_END(DTO)

} // namespace biot
