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
 * @file param_module.h
 * @brief 
 * @author Jerry.Yu (jerry.yu512outlook.com)
 * @version 1.0.0
 * @date 2022-04-04
 * 
 * @copyright MIT License
 * 
 */
#pragma once

#include "basic/defs/reflection.h"
#include "param_module/param_db.h"
#include "param_module/param_device.h"
#include "param_module/param_hw.h"
#include "param_module/param_media.h"
#include "param_module/param_network.h"
#include "param_module/param_storage.h"
#include "param_module/param_subsys.h"

namespace biot {

#include OATPP_CODEGEN_BEGIN(DTO)

class CfgParamModule : public oatpp::DTO {
	DTO_INIT(CfgParamModule, DTO)

	DTO_FIELD(Object<CfgParamDb>, db);
	DTO_FIELD(Object<CfgParamDevice>, device);
	DTO_FIELD(Object<CfgParamHw>, hardware);
	DTO_FIELD(Object<CfgParamMedia>, media);
	DTO_FIELD(Object<CfgParamNetwork>, network);
	DTO_FIELD(Object<CfgParamStorage>, storage);
	DTO_FIELD(Object<CfgParamSubsys>, subsys);
};

#include OATPP_CODEGEN_END(DTO)

} // namespace biot
