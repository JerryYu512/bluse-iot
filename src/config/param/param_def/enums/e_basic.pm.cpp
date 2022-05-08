#include "e_basic.if.h"


namespace biot { 

template <> const char* get_enum_as_str<EBiotAppMode>(EBiotAppMode e) {
	switch(e) {
		case EBiotAppMode::APP_DEVICE_MODE:                 return "EBiotAppMode::APP_DEVICE_MODE";
		case EBiotAppMode::APP_GATEWAY_MODE:                return "EBiotAppMode::APP_GATEWAY_MODE";
		case EBiotAppMode::APP_DEV_GW_MODE:                 return "EBiotAppMode::APP_DEV_GW_MODE";
		default: return nullptr;
	}
}

template <> const char* get_enum_str<EBiotAppMode>(EBiotAppMode e) {
	switch(e) {
		case EBiotAppMode::APP_DEVICE_MODE:                 return "EBiotAppMode::APP_DEVICE_MODE";
		case EBiotAppMode::APP_GATEWAY_MODE:                return "EBiotAppMode::APP_GATEWAY_MODE";
		case EBiotAppMode::APP_DEV_GW_MODE:                 return "EBiotAppMode::APP_DEV_GW_MODE";
		default: return nullptr;
	}
}

template <> EBiotAppMode get_enum_value<EBiotAppMode>(const char* str) {
	static std::map<std::string, EBiotAppMode> emap = {
		{"EBiotAppMode::APP_DEVICE_MODE",                EBiotAppMode::APP_DEVICE_MODE},
		{"EBiotAppMode::APP_GATEWAY_MODE",               EBiotAppMode::APP_GATEWAY_MODE},
		{"EBiotAppMode::APP_DEV_GW_MODE",                EBiotAppMode::APP_DEV_GW_MODE},
	};

	if (!str) { if (sizeof(EBiotAppMode) < sizeof(uint32_t)) { return static_cast<EBiotAppMode>(UINT64_MAX); } else { return static_cast<EBiotAppMode>(UINT64_MAX); } }

	auto key = emap.find(str);

	if (emap.end() == key) { if (sizeof(EBiotAppMode) < sizeof(uint64_t)) { return static_cast<EBiotAppMode>(UINT32_MAX); } else { return static_cast<EBiotAppMode>(UINT64_MAX); } }

	return key->second;
}

template <> bool in_enum_range<EBiotAppMode>(EBiotAppMode e) {
	switch(e) {
		case EBiotAppMode::APP_DEVICE_MODE:                 return true;
		case EBiotAppMode::APP_GATEWAY_MODE:                return true;
		case EBiotAppMode::APP_DEV_GW_MODE:                 return true;
		default: return false;
	}
}


}
