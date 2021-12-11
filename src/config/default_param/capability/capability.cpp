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
 * @file capability.cpp
 * @brief 
 * @author wotsen (astralrovers@outlook.com)
 * @version 1.0.0
 * @date 2021-08-18
 * 
 * @copyright MIT License
 * 
 */
#include "capability.h"
#include "config/default_parameter.h"

namespace ars {

namespace iot {

static parameter_config_t def_capability_hw = {
	"hardware capability",
	"硬件能力级",
	param_t_object,
	"NA",
	param_p_read,
	R"(
	{
		"hardware version": {
			"desc": "硬件版本",
			"type": "string",
			"range": "\\w",
			"permission": "r",
			"value": "hw 20210101 00:00:00"
		},
		"flash size": {
			"desc": "flash大小",
			"type": "unsigned int64",
			"range": "[0,]",
			"permission": "r",
			"value": 2199023255552
		},
		"ram size": {
			"desc": "内存大小",
			"type": "unsigned int64",
			"range": "[0,]",
			"permission": "r",
			"value": 17179869184
		},
		"IO": {
			"desc": "内存大小",
			"type": "object",
			"range": "NA",
			"permission": "r",
			"value": {
				"io num": {
					"desc": "io口数量",
					"type": "unsigned int8",
					"range": "[0,255]",
					"permission": "r",
					"value": 8
				},
				"alarm in": {
					"desc": "告警输入",
					"type": "array",
					"sub type": "unsigned int8",
					"range": "[0,255]",
					"permission": "r",
					"value": [0, 1]
				},
				"alarm out": {
					"desc": "告警输出",
					"type": "array",
					"sub type": "unsigned int8",
					"range": "[0,255]",
					"permission": "r",
					"value": [2, 3]
				}
			}
		},
		"serial": {
			"desc": "串口",
			"type": "object",
			"range": "NA",
			"permission": "r",
			"value": {
				"rs232": {
					"desc": "rs232数量",
					"type": "unsigned int8",
					"range": "[0,255]",
					"permission": "r",
					"value": 1
				},
				"rs485": {
					"desc": "rs485数量",
					"type": "unsigned int8",
					"range": "[0,255]",
					"permission": "r",
					"value": 1
				}
			}
		},
		"network": {
			"desc": "网络能力级",
			"type": "object",
			"range": "NA",
			"permission": "r",
			"value": {
				"rj45": {
					"desc": "rj45数量",
					"type": "unsigned int8",
					"range": "[0,255]",
					"permission": "r",
					"value": 2
				}
			}
		},
		"sdcard": {
			"desc": "sd卡",
			"type": "object",
			"range": "NA",
			"permission": "r",
			"value": {
				"num": {
					"desc": "rj45数量",
					"type": "unsigned int8",
					"range": "[0,255]",
					"permission": "r",
					"value": 4
				},
				"min size": {
					"desc": "sd卡最小容量",
					"type": "unsigned int64",
					"range": "[0,]",
					"permission": "r",
					"value": 17179869184
				},
				"max size": {
					"desc": "sd卡最大容量",
					"type": "unsigned int64",
					"range": "[0,]",
					"permission": "r",
					"value": 2199023255552
				}
			}
		}
	}
	)",
	param_t_string,
	{ }
};

parameter_config_t def_capability = {
	"capability",
	"能力级，不可修改",
	param_t_object,
	"NA",
	param_p_read,
	R"(
	{
		"device serial": {
			"desc": "设备序列号，11位",
			"type": "string",
			"range": "[0-9,a-z,A-Z]{11}",
			"permission": "r",
			"value": "12345678901"
		},
		"device type": {
			"desc": "设备类型",
			"type": "string",
			"range": "\\w",
			"permission": "r",
			"value": "ARS-IOT12345"
		},
		"device sub type": {
			"desc": "设备子类型，一般用于标识设备使用场景",
			"type": "string",
			"range": "\\w",
			"permission": "r",
			"value": "home-camera-ptz"
		}
	}
	)",
	param_t_object,
	{
		&def_capability_hw,
	}
};

} // namespace iot

} // namespace ars