#pragma once

#include <vector>
#include <string>
#include <stdint.h>
#include <iostream>
#include "module_device.pm.h"
#include "module_hw.pm.h"
#include "module_media.pm.h"
#include "module_subsys.pm.h"
#include "module_db.pm.h"
#include "module_network.pm.h"
#include "module_storage.pm.h"

namespace biot { 

typedef struct BiotAppModule_s BiotAppModule;

// 模块配置
struct BiotAppModule_s {
	BiotAppHardware hardware;                                       ///< 硬件配置
	BiotAppDevice device;                                           ///< 设备配置
	BiotAppNetwork network;                                         ///< 网络配置
	BiotAppDb database;                                             ///< 数据库配置
	BiotAppStorage storage;                                         ///< 存储配置
	BiotAppMedia media;                                             ///< 媒体配置
	BiotAppSubsys subsys;                                           ///< 子系统配置
	BiotAppModule_s() {
	}
};


}
