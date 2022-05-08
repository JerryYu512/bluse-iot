#include "param_module.if.h"


namespace biot { 

template <> bool struct2json<BiotAppModule>(const BiotAppModule &st, nlohmann::json &js) {
	{ nlohmann::json node; struct2json(st.hardware, node); js["hardware"] = node; }
	{ nlohmann::json node; struct2json(st.device, node); js["device"] = node; }
	{ nlohmann::json node; struct2json(st.network, node); js["network"] = node; }
	{ nlohmann::json node; struct2json(st.database, node); js["database"] = node; }
	{ nlohmann::json node; struct2json(st.storage, node); js["storage"] = node; }
	{ nlohmann::json node; struct2json(st.media, node); js["media"] = node; }
	{ nlohmann::json node; struct2json(st.subsys, node); js["subsys"] = node; }

	return true;
}

template <> bool json2struct<BiotAppModule>(simdjson::dom::element &js, BiotAppModule &st) {
	BiotAppModule tst;
	{
		simdjson::dom::element val;
		if (simdjson::SUCCESS != js["hardware"].get(val) || !js["hardware"].is_object()) {
			if (false) { std::cerr << "not find [hardware]" << std::endl; }
		} else {
			BiotAppHardware o;
			if (json2struct(val, o)) { tst.hardware = o; }
		}
	}
	{
		simdjson::dom::element val;
		if (simdjson::SUCCESS != js["device"].get(val) || !js["device"].is_object()) {
			if (false) { std::cerr << "not find [device]" << std::endl; }
		} else {
			BiotAppDevice o;
			if (json2struct(val, o)) { tst.device = o; }
		}
	}
	{
		simdjson::dom::element val;
		if (simdjson::SUCCESS != js["network"].get(val) || !js["network"].is_object()) {
			if (false) { std::cerr << "not find [network]" << std::endl; }
		} else {
			BiotAppNetwork o;
			if (json2struct(val, o)) { tst.network = o; }
		}
	}
	{
		simdjson::dom::element val;
		if (simdjson::SUCCESS != js["database"].get(val) || !js["database"].is_object()) {
			if (false) { std::cerr << "not find [database]" << std::endl; }
		} else {
			BiotAppDb o;
			if (json2struct(val, o)) { tst.database = o; }
		}
	}
	{
		simdjson::dom::element val;
		if (simdjson::SUCCESS != js["storage"].get(val) || !js["storage"].is_object()) {
			if (false) { std::cerr << "not find [storage]" << std::endl; }
		} else {
			BiotAppStorage o;
			if (json2struct(val, o)) { tst.storage = o; }
		}
	}
	{
		simdjson::dom::element val;
		if (simdjson::SUCCESS != js["media"].get(val) || !js["media"].is_object()) {
			if (false) { std::cerr << "not find [media]" << std::endl; }
		} else {
			BiotAppMedia o;
			if (json2struct(val, o)) { tst.media = o; }
		}
	}
	{
		simdjson::dom::element val;
		if (simdjson::SUCCESS != js["subsys"].get(val) || !js["subsys"].is_object()) {
			if (false) { std::cerr << "not find [subsys]" << std::endl; }
		} else {
			BiotAppSubsys o;
			if (json2struct(val, o)) { tst.subsys = o; }
		}
	}

	st = tst;
	return true;
}


}
