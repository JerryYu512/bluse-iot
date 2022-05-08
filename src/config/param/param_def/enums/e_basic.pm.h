#pragma once


namespace biot { 

// 可选运行模式
enum class EBiotAppMode {
	APP_DEVICE_MODE                      = 0,                     ///< 设备模式
	APP_GATEWAY_MODE                     = 1,                     ///< 网关模式
	APP_DEV_GW_MODE                      = 2,                     ///< 设备/网关模式
};

}
