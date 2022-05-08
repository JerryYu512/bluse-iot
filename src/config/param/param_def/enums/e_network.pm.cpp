#include "e_network.if.h"


namespace biot { 

template <> const char* get_enum_as_str<BiotAppModulePayload>(BiotAppModulePayload e) {
	switch(e) {
		case BiotAppModulePayload::MODULE_PAYLOAD_RAW:              return "BiotAppModulePayload::MODULE_PAYLOAD_RAW";
		case BiotAppModulePayload::MODULE_PAYLOAD_HTTP:             return "BiotAppModulePayload::MODULE_PAYLOAD_HTTP";
		case BiotAppModulePayload::MODULE_PAYLOAD_JSON:             return "BiotAppModulePayload::MODULE_PAYLOAD_JSON";
		case BiotAppModulePayload::MODULE_PAYLOAD_XML:              return "BiotAppModulePayload::MODULE_PAYLOAD_XML";
		case BiotAppModulePayload::MODULE_PAYLOAD_PROTOBUF:         return "BiotAppModulePayload::MODULE_PAYLOAD_PROTOBUF";
		default: return nullptr;
	}
}

template <> const char* get_enum_str<BiotAppModulePayload>(BiotAppModulePayload e) {
	switch(e) {
		case BiotAppModulePayload::MODULE_PAYLOAD_RAW:              return "BiotAppModulePayload::raw";
		case BiotAppModulePayload::MODULE_PAYLOAD_HTTP:             return "BiotAppModulePayload::http";
		case BiotAppModulePayload::MODULE_PAYLOAD_JSON:             return "BiotAppModulePayload::json";
		case BiotAppModulePayload::MODULE_PAYLOAD_XML:              return "BiotAppModulePayload::xml";
		case BiotAppModulePayload::MODULE_PAYLOAD_PROTOBUF:         return "BiotAppModulePayload::protobuf";
		default: return nullptr;
	}
}

template <> BiotAppModulePayload get_enum_value<BiotAppModulePayload>(const char* str) {
	static std::map<std::string, BiotAppModulePayload> emap = {
		{"BiotAppModulePayload::raw",                    BiotAppModulePayload::MODULE_PAYLOAD_RAW},
		{"BiotAppModulePayload::http",                   BiotAppModulePayload::MODULE_PAYLOAD_HTTP},
		{"BiotAppModulePayload::json",                   BiotAppModulePayload::MODULE_PAYLOAD_JSON},
		{"BiotAppModulePayload::xml",                    BiotAppModulePayload::MODULE_PAYLOAD_XML},
		{"BiotAppModulePayload::protobuf",               BiotAppModulePayload::MODULE_PAYLOAD_PROTOBUF},
	};

	if (!str) { if (sizeof(BiotAppModulePayload) < sizeof(uint32_t)) { return static_cast<BiotAppModulePayload>(UINT64_MAX); } else { return static_cast<BiotAppModulePayload>(UINT64_MAX); } }

	auto key = emap.find(str);

	if (emap.end() == key) { if (sizeof(BiotAppModulePayload) < sizeof(uint64_t)) { return static_cast<BiotAppModulePayload>(UINT32_MAX); } else { return static_cast<BiotAppModulePayload>(UINT64_MAX); } }

	return key->second;
}

template <> bool in_enum_range<BiotAppModulePayload>(BiotAppModulePayload e) {
	switch(e) {
		case BiotAppModulePayload::MODULE_PAYLOAD_RAW:              return true;
		case BiotAppModulePayload::MODULE_PAYLOAD_HTTP:             return true;
		case BiotAppModulePayload::MODULE_PAYLOAD_JSON:             return true;
		case BiotAppModulePayload::MODULE_PAYLOAD_XML:              return true;
		case BiotAppModulePayload::MODULE_PAYLOAD_PROTOBUF:         return true;
		default: return false;
	}
}

template <> const char* get_enum_as_str<BiotAppModuleProtocol>(BiotAppModuleProtocol e) {
	switch(e) {
		case BiotAppModuleProtocol::MODULE_PROTOC_MQTT:              return "BiotAppModuleProtocol::MODULE_PROTOC_MQTT";
		case BiotAppModuleProtocol::MODULE_PROTOC_NNG:               return "BiotAppModuleProtocol::MODULE_PROTOC_NNG";
		case BiotAppModuleProtocol::MODULE_PROTOC_PROTOBUF:          return "BiotAppModuleProtocol::MODULE_PROTOC_PROTOBUF";
		default: return nullptr;
	}
}

template <> const char* get_enum_str<BiotAppModuleProtocol>(BiotAppModuleProtocol e) {
	switch(e) {
		case BiotAppModuleProtocol::MODULE_PROTOC_MQTT:              return "BiotAppModuleProtocol::mqtt";
		case BiotAppModuleProtocol::MODULE_PROTOC_NNG:               return "BiotAppModuleProtocol::nng";
		case BiotAppModuleProtocol::MODULE_PROTOC_PROTOBUF:          return "BiotAppModuleProtocol::protobuf";
		default: return nullptr;
	}
}

template <> BiotAppModuleProtocol get_enum_value<BiotAppModuleProtocol>(const char* str) {
	static std::map<std::string, BiotAppModuleProtocol> emap = {
		{"BiotAppModuleProtocol::mqtt",                  BiotAppModuleProtocol::MODULE_PROTOC_MQTT},
		{"BiotAppModuleProtocol::nng",                   BiotAppModuleProtocol::MODULE_PROTOC_NNG},
		{"BiotAppModuleProtocol::protobuf",              BiotAppModuleProtocol::MODULE_PROTOC_PROTOBUF},
	};

	if (!str) { if (sizeof(BiotAppModuleProtocol) < sizeof(uint32_t)) { return static_cast<BiotAppModuleProtocol>(UINT64_MAX); } else { return static_cast<BiotAppModuleProtocol>(UINT64_MAX); } }

	auto key = emap.find(str);

	if (emap.end() == key) { if (sizeof(BiotAppModuleProtocol) < sizeof(uint64_t)) { return static_cast<BiotAppModuleProtocol>(UINT32_MAX); } else { return static_cast<BiotAppModuleProtocol>(UINT64_MAX); } }

	return key->second;
}

template <> bool in_enum_range<BiotAppModuleProtocol>(BiotAppModuleProtocol e) {
	switch(e) {
		case BiotAppModuleProtocol::MODULE_PROTOC_MQTT:              return true;
		case BiotAppModuleProtocol::MODULE_PROTOC_NNG:               return true;
		case BiotAppModuleProtocol::MODULE_PROTOC_PROTOBUF:          return true;
		default: return false;
	}
}

template <> const char* get_enum_as_str<NetCfgType>(NetCfgType e) {
	switch(e) {
		case NetCfgType::NET_CFG_MANUAL:                  return "NetCfgType::NET_CFG_MANUAL";
		case NetCfgType::NET_CFG_AUTO:                    return "NetCfgType::NET_CFG_AUTO";
		default: return nullptr;
	}
}

template <> const char* get_enum_str<NetCfgType>(NetCfgType e) {
	switch(e) {
		case NetCfgType::NET_CFG_MANUAL:                  return "NetCfgType::NET_CFG_MANUAL";
		case NetCfgType::NET_CFG_AUTO:                    return "NetCfgType::NET_CFG_AUTO";
		default: return nullptr;
	}
}

template <> NetCfgType get_enum_value<NetCfgType>(const char* str) {
	static std::map<std::string, NetCfgType> emap = {
		{"NetCfgType::NET_CFG_MANUAL",                   NetCfgType::NET_CFG_MANUAL},
		{"NetCfgType::NET_CFG_AUTO",                     NetCfgType::NET_CFG_AUTO},
	};

	if (!str) { if (sizeof(NetCfgType) < sizeof(uint32_t)) { return static_cast<NetCfgType>(UINT64_MAX); } else { return static_cast<NetCfgType>(UINT64_MAX); } }

	auto key = emap.find(str);

	if (emap.end() == key) { if (sizeof(NetCfgType) < sizeof(uint64_t)) { return static_cast<NetCfgType>(UINT32_MAX); } else { return static_cast<NetCfgType>(UINT64_MAX); } }

	return key->second;
}

template <> bool in_enum_range<NetCfgType>(NetCfgType e) {
	switch(e) {
		case NetCfgType::NET_CFG_MANUAL:                  return true;
		case NetCfgType::NET_CFG_AUTO:                    return true;
		default: return false;
	}
}

template <> const char* get_enum_as_str<NetIfRate>(NetIfRate e) {
	switch(e) {
		case NetIfRate::NET_IF_RATE_100M:                return "NetIfRate::NET_IF_RATE_100M";
		case NetIfRate::NET_IF_RATE_1000M:               return "NetIfRate::NET_IF_RATE_1000M";
		default: return nullptr;
	}
}

template <> const char* get_enum_str<NetIfRate>(NetIfRate e) {
	switch(e) {
		case NetIfRate::NET_IF_RATE_100M:                return "NetIfRate::NET_IF_RATE_100M";
		case NetIfRate::NET_IF_RATE_1000M:               return "NetIfRate::NET_IF_RATE_1000M";
		default: return nullptr;
	}
}

template <> NetIfRate get_enum_value<NetIfRate>(const char* str) {
	static std::map<std::string, NetIfRate> emap = {
		{"NetIfRate::NET_IF_RATE_100M",                  NetIfRate::NET_IF_RATE_100M},
		{"NetIfRate::NET_IF_RATE_1000M",                 NetIfRate::NET_IF_RATE_1000M},
	};

	if (!str) { if (sizeof(NetIfRate) < sizeof(uint32_t)) { return static_cast<NetIfRate>(UINT64_MAX); } else { return static_cast<NetIfRate>(UINT64_MAX); } }

	auto key = emap.find(str);

	if (emap.end() == key) { if (sizeof(NetIfRate) < sizeof(uint64_t)) { return static_cast<NetIfRate>(UINT32_MAX); } else { return static_cast<NetIfRate>(UINT64_MAX); } }

	return key->second;
}

template <> bool in_enum_range<NetIfRate>(NetIfRate e) {
	switch(e) {
		case NetIfRate::NET_IF_RATE_100M:                return true;
		case NetIfRate::NET_IF_RATE_1000M:               return true;
		default: return false;
	}
}

template <> const char* get_enum_as_str<NetLanType>(NetLanType e) {
	switch(e) {
		case NetLanType::LAN_WORK_10M_HALF:               return "NetLanType::LAN_WORK_10M_HALF";
		case NetLanType::LAN_WORK_10M_FULL:               return "NetLanType::LAN_WORK_10M_FULL";
		case NetLanType::LAN_WORK_100M_HALF:              return "NetLanType::LAN_WORK_100M_HALF";
		case NetLanType::LAN_WORK_100M_FULL:              return "NetLanType::LAN_WORK_100M_FULL";
		case NetLanType::LAN_WORK_AUTO:                   return "NetLanType::LAN_WORK_AUTO";
		case NetLanType::LAN_WORK_1G_FULL:                return "NetLanType::LAN_WORK_1G_FULL";
		default: return nullptr;
	}
}

template <> const char* get_enum_str<NetLanType>(NetLanType e) {
	switch(e) {
		case NetLanType::LAN_WORK_10M_HALF:               return "NetLanType::10M-half";
		case NetLanType::LAN_WORK_10M_FULL:               return "NetLanType::10M-full";
		case NetLanType::LAN_WORK_100M_HALF:              return "NetLanType::100M-half";
		case NetLanType::LAN_WORK_100M_FULL:              return "NetLanType::100M-full";
		case NetLanType::LAN_WORK_AUTO:                   return "NetLanType::auto";
		case NetLanType::LAN_WORK_1G_FULL:                return "NetLanType::1G-full";
		default: return nullptr;
	}
}

template <> NetLanType get_enum_value<NetLanType>(const char* str) {
	static std::map<std::string, NetLanType> emap = {
		{"NetLanType::10M-half",                         NetLanType::LAN_WORK_10M_HALF},
		{"NetLanType::10M-full",                         NetLanType::LAN_WORK_10M_FULL},
		{"NetLanType::100M-half",                        NetLanType::LAN_WORK_100M_HALF},
		{"NetLanType::100M-full",                        NetLanType::LAN_WORK_100M_FULL},
		{"NetLanType::auto",                             NetLanType::LAN_WORK_AUTO},
		{"NetLanType::1G-full",                          NetLanType::LAN_WORK_1G_FULL},
	};

	if (!str) { if (sizeof(NetLanType) < sizeof(uint32_t)) { return static_cast<NetLanType>(UINT64_MAX); } else { return static_cast<NetLanType>(UINT64_MAX); } }

	auto key = emap.find(str);

	if (emap.end() == key) { if (sizeof(NetLanType) < sizeof(uint64_t)) { return static_cast<NetLanType>(UINT32_MAX); } else { return static_cast<NetLanType>(UINT64_MAX); } }

	return key->second;
}

template <> bool in_enum_range<NetLanType>(NetLanType e) {
	switch(e) {
		case NetLanType::LAN_WORK_10M_HALF:               return true;
		case NetLanType::LAN_WORK_10M_FULL:               return true;
		case NetLanType::LAN_WORK_100M_HALF:              return true;
		case NetLanType::LAN_WORK_100M_FULL:              return true;
		case NetLanType::LAN_WORK_AUTO:                   return true;
		case NetLanType::LAN_WORK_1G_FULL:                return true;
		default: return false;
	}
}

template <> const char* get_enum_as_str<WireLessIfMode>(WireLessIfMode e) {
	switch(e) {
		case WireLessIfMode::WIRELESS_IF_AUTO:                return "WireLessIfMode::WIRELESS_IF_AUTO";
		case WireLessIfMode::WIRELESS_IF_LAN:                 return "WireLessIfMode::WIRELESS_IF_LAN";
		default: return nullptr;
	}
}

template <> const char* get_enum_str<WireLessIfMode>(WireLessIfMode e) {
	switch(e) {
		case WireLessIfMode::WIRELESS_IF_AUTO:                return "WireLessIfMode::WIRELESS_IF_AUTO";
		case WireLessIfMode::WIRELESS_IF_LAN:                 return "WireLessIfMode::WIRELESS_IF_LAN";
		default: return nullptr;
	}
}

template <> WireLessIfMode get_enum_value<WireLessIfMode>(const char* str) {
	static std::map<std::string, WireLessIfMode> emap = {
		{"WireLessIfMode::WIRELESS_IF_AUTO",             WireLessIfMode::WIRELESS_IF_AUTO},
		{"WireLessIfMode::WIRELESS_IF_LAN",              WireLessIfMode::WIRELESS_IF_LAN},
	};

	if (!str) { if (sizeof(WireLessIfMode) < sizeof(uint32_t)) { return static_cast<WireLessIfMode>(UINT64_MAX); } else { return static_cast<WireLessIfMode>(UINT64_MAX); } }

	auto key = emap.find(str);

	if (emap.end() == key) { if (sizeof(WireLessIfMode) < sizeof(uint64_t)) { return static_cast<WireLessIfMode>(UINT32_MAX); } else { return static_cast<WireLessIfMode>(UINT64_MAX); } }

	return key->second;
}

template <> bool in_enum_range<WireLessIfMode>(WireLessIfMode e) {
	switch(e) {
		case WireLessIfMode::WIRELESS_IF_AUTO:                return true;
		case WireLessIfMode::WIRELESS_IF_LAN:                 return true;
		default: return false;
	}
}

template <> const char* get_enum_as_str<WireLessSecMode>(WireLessSecMode e) {
	switch(e) {
		case WireLessSecMode::WIRELESS_SEC_NONE:               return "WireLessSecMode::WIRELESS_SEC_NONE";
		case WireLessSecMode::WIRELESS_SEC_WEP:                return "WireLessSecMode::WIRELESS_SEC_WEP";
		case WireLessSecMode::WIRELESS_SEC_WPA_PSK:            return "WireLessSecMode::WIRELESS_SEC_WPA_PSK";
		case WireLessSecMode::WIRELESS_SEC_WPA_ENTERPRISE:     return "WireLessSecMode::WIRELESS_SEC_WPA_ENTERPRISE";
		case WireLessSecMode::WIRELESS_SEC_WPA2_PSK:           return "WireLessSecMode::WIRELESS_SEC_WPA2_PSK";
		default: return nullptr;
	}
}

template <> const char* get_enum_str<WireLessSecMode>(WireLessSecMode e) {
	switch(e) {
		case WireLessSecMode::WIRELESS_SEC_NONE:               return "WireLessSecMode::WIRELESS_SEC_NONE";
		case WireLessSecMode::WIRELESS_SEC_WEP:                return "WireLessSecMode::WIRELESS_SEC_WEP";
		case WireLessSecMode::WIRELESS_SEC_WPA_PSK:            return "WireLessSecMode::WIRELESS_SEC_WPA_PSK";
		case WireLessSecMode::WIRELESS_SEC_WPA_ENTERPRISE:     return "WireLessSecMode::WIRELESS_SEC_WPA_ENTERPRISE";
		case WireLessSecMode::WIRELESS_SEC_WPA2_PSK:           return "WireLessSecMode::WIRELESS_SEC_WPA2_PSK";
		default: return nullptr;
	}
}

template <> WireLessSecMode get_enum_value<WireLessSecMode>(const char* str) {
	static std::map<std::string, WireLessSecMode> emap = {
		{"WireLessSecMode::WIRELESS_SEC_NONE",           WireLessSecMode::WIRELESS_SEC_NONE},
		{"WireLessSecMode::WIRELESS_SEC_WEP",            WireLessSecMode::WIRELESS_SEC_WEP},
		{"WireLessSecMode::WIRELESS_SEC_WPA_PSK",        WireLessSecMode::WIRELESS_SEC_WPA_PSK},
		{"WireLessSecMode::WIRELESS_SEC_WPA_ENTERPRISE", WireLessSecMode::WIRELESS_SEC_WPA_ENTERPRISE},
		{"WireLessSecMode::WIRELESS_SEC_WPA2_PSK",       WireLessSecMode::WIRELESS_SEC_WPA2_PSK},
	};

	if (!str) { if (sizeof(WireLessSecMode) < sizeof(uint32_t)) { return static_cast<WireLessSecMode>(UINT64_MAX); } else { return static_cast<WireLessSecMode>(UINT64_MAX); } }

	auto key = emap.find(str);

	if (emap.end() == key) { if (sizeof(WireLessSecMode) < sizeof(uint64_t)) { return static_cast<WireLessSecMode>(UINT32_MAX); } else { return static_cast<WireLessSecMode>(UINT64_MAX); } }

	return key->second;
}

template <> bool in_enum_range<WireLessSecMode>(WireLessSecMode e) {
	switch(e) {
		case WireLessSecMode::WIRELESS_SEC_NONE:               return true;
		case WireLessSecMode::WIRELESS_SEC_WEP:                return true;
		case WireLessSecMode::WIRELESS_SEC_WPA_PSK:            return true;
		case WireLessSecMode::WIRELESS_SEC_WPA_ENTERPRISE:     return true;
		case WireLessSecMode::WIRELESS_SEC_WPA2_PSK:           return true;
		default: return false;
	}
}

template <> const char* get_enum_as_str<WireLessWepAuthType>(WireLessWepAuthType e) {
	switch(e) {
		case WireLessWepAuthType::WIRELESS_WEPAUTH_OPEN:           return "WireLessWepAuthType::WIRELESS_WEPAUTH_OPEN";
		case WireLessWepAuthType::WIRELESS_WEPAUTH_SHARE:          return "WireLessWepAuthType::WIRELESS_WEPAUTH_SHARE";
		default: return nullptr;
	}
}

template <> const char* get_enum_str<WireLessWepAuthType>(WireLessWepAuthType e) {
	switch(e) {
		case WireLessWepAuthType::WIRELESS_WEPAUTH_OPEN:           return "WireLessWepAuthType::WIRELESS_WEPAUTH_OPEN";
		case WireLessWepAuthType::WIRELESS_WEPAUTH_SHARE:          return "WireLessWepAuthType::WIRELESS_WEPAUTH_SHARE";
		default: return nullptr;
	}
}

template <> WireLessWepAuthType get_enum_value<WireLessWepAuthType>(const char* str) {
	static std::map<std::string, WireLessWepAuthType> emap = {
		{"WireLessWepAuthType::WIRELESS_WEPAUTH_OPEN",   WireLessWepAuthType::WIRELESS_WEPAUTH_OPEN},
		{"WireLessWepAuthType::WIRELESS_WEPAUTH_SHARE",  WireLessWepAuthType::WIRELESS_WEPAUTH_SHARE},
	};

	if (!str) { if (sizeof(WireLessWepAuthType) < sizeof(uint32_t)) { return static_cast<WireLessWepAuthType>(UINT64_MAX); } else { return static_cast<WireLessWepAuthType>(UINT64_MAX); } }

	auto key = emap.find(str);

	if (emap.end() == key) { if (sizeof(WireLessWepAuthType) < sizeof(uint64_t)) { return static_cast<WireLessWepAuthType>(UINT32_MAX); } else { return static_cast<WireLessWepAuthType>(UINT64_MAX); } }

	return key->second;
}

template <> bool in_enum_range<WireLessWepAuthType>(WireLessWepAuthType e) {
	switch(e) {
		case WireLessWepAuthType::WIRELESS_WEPAUTH_OPEN:           return true;
		case WireLessWepAuthType::WIRELESS_WEPAUTH_SHARE:          return true;
		default: return false;
	}
}

template <> const char* get_enum_as_str<WireLessWepKeyLen>(WireLessWepKeyLen e) {
	switch(e) {
		case WireLessWepKeyLen::WIRELESS_WEPKEY_LEN64:           return "WireLessWepKeyLen::WIRELESS_WEPKEY_LEN64";
		case WireLessWepKeyLen::WIRELESS_WEPKEY_LEN128:          return "WireLessWepKeyLen::WIRELESS_WEPKEY_LEN128";
		case WireLessWepKeyLen::WIRELESS_WEPKEY_LEN152:          return "WireLessWepKeyLen::WIRELESS_WEPKEY_LEN152";
		default: return nullptr;
	}
}

template <> const char* get_enum_str<WireLessWepKeyLen>(WireLessWepKeyLen e) {
	switch(e) {
		case WireLessWepKeyLen::WIRELESS_WEPKEY_LEN64:           return "WireLessWepKeyLen::WIRELESS_WEPKEY_LEN64";
		case WireLessWepKeyLen::WIRELESS_WEPKEY_LEN128:          return "WireLessWepKeyLen::WIRELESS_WEPKEY_LEN128";
		case WireLessWepKeyLen::WIRELESS_WEPKEY_LEN152:          return "WireLessWepKeyLen::WIRELESS_WEPKEY_LEN152";
		default: return nullptr;
	}
}

template <> WireLessWepKeyLen get_enum_value<WireLessWepKeyLen>(const char* str) {
	static std::map<std::string, WireLessWepKeyLen> emap = {
		{"WireLessWepKeyLen::WIRELESS_WEPKEY_LEN64",     WireLessWepKeyLen::WIRELESS_WEPKEY_LEN64},
		{"WireLessWepKeyLen::WIRELESS_WEPKEY_LEN128",    WireLessWepKeyLen::WIRELESS_WEPKEY_LEN128},
		{"WireLessWepKeyLen::WIRELESS_WEPKEY_LEN152",    WireLessWepKeyLen::WIRELESS_WEPKEY_LEN152},
	};

	if (!str) { if (sizeof(WireLessWepKeyLen) < sizeof(uint32_t)) { return static_cast<WireLessWepKeyLen>(UINT64_MAX); } else { return static_cast<WireLessWepKeyLen>(UINT64_MAX); } }

	auto key = emap.find(str);

	if (emap.end() == key) { if (sizeof(WireLessWepKeyLen) < sizeof(uint64_t)) { return static_cast<WireLessWepKeyLen>(UINT32_MAX); } else { return static_cast<WireLessWepKeyLen>(UINT64_MAX); } }

	return key->second;
}

template <> bool in_enum_range<WireLessWepKeyLen>(WireLessWepKeyLen e) {
	switch(e) {
		case WireLessWepKeyLen::WIRELESS_WEPKEY_LEN64:           return true;
		case WireLessWepKeyLen::WIRELESS_WEPKEY_LEN128:          return true;
		case WireLessWepKeyLen::WIRELESS_WEPKEY_LEN152:          return true;
		default: return false;
	}
}

template <> const char* get_enum_as_str<WireLessWepKeyType>(WireLessWepKeyType e) {
	switch(e) {
		case WireLessWepKeyType::WIRELESS_WEPKEY_HEX:             return "WireLessWepKeyType::WIRELESS_WEPKEY_HEX";
		case WireLessWepKeyType::WIRELESS_WEPKEY_ASCII:           return "WireLessWepKeyType::WIRELESS_WEPKEY_ASCII";
		default: return nullptr;
	}
}

template <> const char* get_enum_str<WireLessWepKeyType>(WireLessWepKeyType e) {
	switch(e) {
		case WireLessWepKeyType::WIRELESS_WEPKEY_HEX:             return "WireLessWepKeyType::WIRELESS_WEPKEY_HEX";
		case WireLessWepKeyType::WIRELESS_WEPKEY_ASCII:           return "WireLessWepKeyType::WIRELESS_WEPKEY_ASCII";
		default: return nullptr;
	}
}

template <> WireLessWepKeyType get_enum_value<WireLessWepKeyType>(const char* str) {
	static std::map<std::string, WireLessWepKeyType> emap = {
		{"WireLessWepKeyType::WIRELESS_WEPKEY_HEX",      WireLessWepKeyType::WIRELESS_WEPKEY_HEX},
		{"WireLessWepKeyType::WIRELESS_WEPKEY_ASCII",    WireLessWepKeyType::WIRELESS_WEPKEY_ASCII},
	};

	if (!str) { if (sizeof(WireLessWepKeyType) < sizeof(uint32_t)) { return static_cast<WireLessWepKeyType>(UINT64_MAX); } else { return static_cast<WireLessWepKeyType>(UINT64_MAX); } }

	auto key = emap.find(str);

	if (emap.end() == key) { if (sizeof(WireLessWepKeyType) < sizeof(uint64_t)) { return static_cast<WireLessWepKeyType>(UINT32_MAX); } else { return static_cast<WireLessWepKeyType>(UINT64_MAX); } }

	return key->second;
}

template <> bool in_enum_range<WireLessWepKeyType>(WireLessWepKeyType e) {
	switch(e) {
		case WireLessWepKeyType::WIRELESS_WEPKEY_HEX:             return true;
		case WireLessWepKeyType::WIRELESS_WEPKEY_ASCII:           return true;
		default: return false;
	}
}

template <> const char* get_enum_as_str<WireLessWorkMode>(WireLessWorkMode e) {
	switch(e) {
		case WireLessWorkMode::WIRELESS_WORK_MANAGED:           return "WireLessWorkMode::WIRELESS_WORK_MANAGED";
		case WireLessWorkMode::WIRELESS_WORK_AD_HOC:            return "WireLessWorkMode::WIRELESS_WORK_AD_HOC";
		default: return nullptr;
	}
}

template <> const char* get_enum_str<WireLessWorkMode>(WireLessWorkMode e) {
	switch(e) {
		case WireLessWorkMode::WIRELESS_WORK_MANAGED:           return "WireLessWorkMode::WIRELESS_WORK_MANAGED";
		case WireLessWorkMode::WIRELESS_WORK_AD_HOC:            return "WireLessWorkMode::WIRELESS_WORK_AD_HOC";
		default: return nullptr;
	}
}

template <> WireLessWorkMode get_enum_value<WireLessWorkMode>(const char* str) {
	static std::map<std::string, WireLessWorkMode> emap = {
		{"WireLessWorkMode::WIRELESS_WORK_MANAGED",      WireLessWorkMode::WIRELESS_WORK_MANAGED},
		{"WireLessWorkMode::WIRELESS_WORK_AD_HOC",       WireLessWorkMode::WIRELESS_WORK_AD_HOC},
	};

	if (!str) { if (sizeof(WireLessWorkMode) < sizeof(uint32_t)) { return static_cast<WireLessWorkMode>(UINT64_MAX); } else { return static_cast<WireLessWorkMode>(UINT64_MAX); } }

	auto key = emap.find(str);

	if (emap.end() == key) { if (sizeof(WireLessWorkMode) < sizeof(uint64_t)) { return static_cast<WireLessWorkMode>(UINT32_MAX); } else { return static_cast<WireLessWorkMode>(UINT64_MAX); } }

	return key->second;
}

template <> bool in_enum_range<WireLessWorkMode>(WireLessWorkMode e) {
	switch(e) {
		case WireLessWorkMode::WIRELESS_WORK_MANAGED:           return true;
		case WireLessWorkMode::WIRELESS_WORK_AD_HOC:            return true;
		default: return false;
	}
}

template <> const char* get_enum_as_str<WireLessWpaEncryptType>(WireLessWpaEncryptType e) {
	switch(e) {
		case WireLessWpaEncryptType::WIRELESS_WPA_ENCRYPT_AES:        return "WireLessWpaEncryptType::WIRELESS_WPA_ENCRYPT_AES";
		case WireLessWpaEncryptType::WIRELESS_WPA_ENCRYPT_TKIP:       return "WireLessWpaEncryptType::WIRELESS_WPA_ENCRYPT_TKIP";
		default: return nullptr;
	}
}

template <> const char* get_enum_str<WireLessWpaEncryptType>(WireLessWpaEncryptType e) {
	switch(e) {
		case WireLessWpaEncryptType::WIRELESS_WPA_ENCRYPT_AES:        return "WireLessWpaEncryptType::WIRELESS_WPA_ENCRYPT_AES";
		case WireLessWpaEncryptType::WIRELESS_WPA_ENCRYPT_TKIP:       return "WireLessWpaEncryptType::WIRELESS_WPA_ENCRYPT_TKIP";
		default: return nullptr;
	}
}

template <> WireLessWpaEncryptType get_enum_value<WireLessWpaEncryptType>(const char* str) {
	static std::map<std::string, WireLessWpaEncryptType> emap = {
		{"WireLessWpaEncryptType::WIRELESS_WPA_ENCRYPT_AES",WireLessWpaEncryptType::WIRELESS_WPA_ENCRYPT_AES},
		{"WireLessWpaEncryptType::WIRELESS_WPA_ENCRYPT_TKIP",WireLessWpaEncryptType::WIRELESS_WPA_ENCRYPT_TKIP},
	};

	if (!str) { if (sizeof(WireLessWpaEncryptType) < sizeof(uint32_t)) { return static_cast<WireLessWpaEncryptType>(UINT64_MAX); } else { return static_cast<WireLessWpaEncryptType>(UINT64_MAX); } }

	auto key = emap.find(str);

	if (emap.end() == key) { if (sizeof(WireLessWpaEncryptType) < sizeof(uint64_t)) { return static_cast<WireLessWpaEncryptType>(UINT32_MAX); } else { return static_cast<WireLessWpaEncryptType>(UINT64_MAX); } }

	return key->second;
}

template <> bool in_enum_range<WireLessWpaEncryptType>(WireLessWpaEncryptType e) {
	switch(e) {
		case WireLessWpaEncryptType::WIRELESS_WPA_ENCRYPT_AES:        return true;
		case WireLessWpaEncryptType::WIRELESS_WPA_ENCRYPT_TKIP:       return true;
		default: return false;
	}
}


}
