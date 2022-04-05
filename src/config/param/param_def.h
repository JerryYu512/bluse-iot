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
#include "product/product.h"

namespace biot {

#include OATPP_CODEGEN_BEGIN(DTO)

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

	// 分模块
	DTO_FIELD(Object<CfgParamBasic>, basic);
	DTO_FIELD(Object<CfgParamSys>, sys);
	DTO_FIELD(Object<CfgParamModule>, module);
	
	// 产品参数
	DTO_FIELD(Object<CfgParamProduct>, product);
};

#include OATPP_CODEGEN_END(DTO)

} // namespace biot
