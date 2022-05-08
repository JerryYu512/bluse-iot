#pragma once


namespace biot { 

// 应用层协议类型
enum class BiotAppModulePayload {
	MODULE_PAYLOAD_RAW                   = 0,                     ///< 二进制[str:raw]
	MODULE_PAYLOAD_HTTP                  = 1,                     ///< http[str:http]
	MODULE_PAYLOAD_JSON                  = 2,                     ///< json[str:json]
	MODULE_PAYLOAD_XML                   = 3,                     ///< xml[str:xml]
	MODULE_PAYLOAD_PROTOBUF              = 4,                     ///< protobuf[str:protobuf]
};
// 模块间通信协议
enum class BiotAppModuleProtocol {
	MODULE_PROTOC_MQTT                   = 0,                     ///< mqtt[str:mqtt]
	MODULE_PROTOC_NNG                    = 1,                     ///< nng[str:nng]
	MODULE_PROTOC_PROTOBUF               = 2,                     ///< protobuf[str:protobuf]
};
// 网络配置方式
enum class NetCfgType {
	NET_CFG_MANUAL                       = 0,                     ///< 手动配置
	NET_CFG_AUTO                         = 1,                     ///< 自动获取
};
// 网口速率
enum class NetIfRate {
	NET_IF_RATE_100M                     = 0,                     ///< 百兆网口
	NET_IF_RATE_1000M                    = 1,                     ///< 千兆网口
};
// 有线网类型
enum class NetLanType {
	LAN_WORK_10M_HALF                    = 0,                     ///< 10M半双工[str:10M-half]
	LAN_WORK_10M_FULL                    = 1,                     ///< 10全双工[str:10M-full]
	LAN_WORK_100M_HALF                   = 2,                     ///< 100M半双工[str:100M-half]
	LAN_WORK_100M_FULL                   = 3,                     ///< 100M全双工[str:100M-full]
	LAN_WORK_AUTO                        = 4,                     ///< 自适应[str:auto]
	LAN_WORK_1G_FULL                     = 5,                     ///< 1G全双工[str:1G-full]
};
// 无线网网络接口模式
enum class WireLessIfMode {
	WIRELESS_IF_AUTO                     = 0,                     ///< 自动切换
	WIRELESS_IF_LAN                      = 1,                     ///< 有线模式
};
// 无线安全模式
enum class WireLessSecMode {
	WIRELESS_SEC_NONE                    = 0,                     ///< 不加密
	WIRELESS_SEC_WEP                     = 1,                     ///< WEP
	WIRELESS_SEC_WPA_PSK                 = 2,                     ///< WPA-PSK
	WIRELESS_SEC_WPA_ENTERPRISE          = 3,                     ///< WPA-enterprise
	WIRELESS_SEC_WPA2_PSK                = 4,                     ///< WPA2-PSK
};
// WEP认证类型
enum class WireLessWepAuthType {
	WIRELESS_WEPAUTH_OPEN                = 0,                     ///< 开放式
	WIRELESS_WEPAUTH_SHARE               = 1,                     ///< 共享式
};
// WEP密钥长度
enum class WireLessWepKeyLen {
	WIRELESS_WEPKEY_LEN64                = 0,                     ///< 64位
	WIRELESS_WEPKEY_LEN128               = 1,                     ///< 128位
	WIRELESS_WEPKEY_LEN152               = 2,                     ///< 152位
};
// WEP密钥类型
enum class WireLessWepKeyType {
	WIRELESS_WEPKEY_HEX                  = 0,                     ///< 16进制
	WIRELESS_WEPKEY_ASCII                = 1,                     ///< ASCII码
};
// 无线工作模式
enum class WireLessWorkMode {
	WIRELESS_WORK_MANAGED                = 0,                     ///< managed
	WIRELESS_WORK_AD_HOC                 = 1,                     ///< ad hoc
};
// WPA加密类型
enum class WireLessWpaEncryptType {
	WIRELESS_WPA_ENCRYPT_AES             = 0,                     ///< AES
	WIRELESS_WPA_ENCRYPT_TKIP            = 1,                     ///< TKIP
};

}
