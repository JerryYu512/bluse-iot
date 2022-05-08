// 配置参数根节点.
#pragma once

#include <vector>
#include <string>
#include <stdint.h>

#include <iostream>
#include "param_module.pm.h"
#include "param_basic.pm.h"
#include "param_system.pm.h"
#include "param_product.pm.h"

namespace biot { 

typedef struct BiotAppParam_s BiotAppParam;

// BIOT应用程序配置参数
struct BiotAppParam_s {
	std::string uuid;                                               ///< 配置参数文件唯一标识，用于校验[eg:03948b6f-9c67-4a14-a53d-2db53466a4e0]
	std::string exec_uuid;                                          ///< 执行程序唯一标识[eg:03948b6f-9c67-4a14-a53d-2db53466a4e0]
	uint32_t version;                                               ///< 配置参数版本号
	std::string device_name;                                        ///< 设备名称[eg:biot 01]
	std::string device_id;                                          ///< 设备id[eg:00000000000][reg:\d{11}]
	BiotAppBasicParam basic;                                        ///< 基础配置参数
	BiotAppSystem system;                                           ///< 系统配置参数
	BiotAppModule modules;                                          ///< 功能模块配置参数
	BiotAppProduct product;                                         ///< 产品配置参数
	BiotAppParam_s() {
		uuid = "03948b6f-9c67-4a14-a53d-2db53466a4e0";
		exec_uuid = "03948b6f-9c67-4a14-a53d-2db53466a4e0";
		version = 0;
		device_name = "biot 01";
		device_id = "00000000000";
	}
};


}
