// 配置参数根节点.
#include "param.if.h"



namespace biot { 

template <> bool struct2json<BiotAppParam>(const BiotAppParam &st, nlohmann::json &js) {
	{ js["uuid"] = st.uuid; }
	{ js["exec_uuid"] = st.exec_uuid; }
	{ js["version"] = st.version; }
	{ js["device_name"] = st.device_name; }
	{ js["device_id"] = st.device_id; }
	{ nlohmann::json node; struct2json(st.basic, node); js["basic"] = node; }
	{ nlohmann::json node; struct2json(st.system, node); js["system"] = node; }
	{ nlohmann::json node; struct2json(st.modules, node); js["modules"] = node; }
	{ nlohmann::json node; struct2json(st.product, node); js["product"] = node; }

	return true;
}

template <> bool json2struct<BiotAppParam>(simdjson::dom::element &js, BiotAppParam &st) {
	BiotAppParam tst;
	{
		const char* val = nullptr;
		if (simdjson::SUCCESS != js["uuid"].get(val) || !js["uuid"].is_string() || !val) {
			if (false) { std::cerr << "not find [uuid]" << std::endl; }
			const char* d = "03948b6f-9c67-4a14-a53d-2db53466a4e0";
			if (d) { tst.uuid = d; }
		} else { tst.uuid = val; }
	}
 	{
		const char* val = nullptr;
		if (simdjson::SUCCESS != js["exec_uuid"].get(val) || !js["exec_uuid"].is_string() || !val) {
			if (false) { std::cerr << "not find [exec_uuid]" << std::endl; }
			const char* d = "03948b6f-9c67-4a14-a53d-2db53466a4e0";
			if (d) { tst.exec_uuid = d; }
		} else { tst.exec_uuid = val; }
	}
 	{
		uint64_t val = 0;
		if (simdjson::SUCCESS != js["version"].get(val) || !js["version"].is_number()) {
			if (false) { std::cerr << "not find [version]" << std::endl; }
				tst.version = 0;
			} else { tst.version = static_cast<uint32_t>(val);
		}
	}
 	{
		const char* val = nullptr;
		if (simdjson::SUCCESS != js["device_name"].get(val) || !js["device_name"].is_string() || !val) {
			if (false) { std::cerr << "not find [device_name]" << std::endl; }
			const char* d = "biot 01";
			if (d) { tst.device_name = d; }
		} else { tst.device_name = val; }
	}
 	{
		const char* val = nullptr;
		if (simdjson::SUCCESS != js["device_id"].get(val) || !js["device_id"].is_string() || !val) {
			if (false) { std::cerr << "not find [device_id]" << std::endl; }
			const char* d = "00000000000";
			if (d) { tst.device_id = d; }
		} else { tst.device_id = val; }
	}
 	{
		simdjson::dom::element val;
		if (simdjson::SUCCESS != js["basic"].get(val) || !js["basic"].is_object()) {
			if (false) { std::cerr << "not find [basic]" << std::endl; }
		} else {
			BiotAppBasicParam o;
			if (json2struct(val, o)) { tst.basic = o; }
		}
	}
	{
		simdjson::dom::element val;
		if (simdjson::SUCCESS != js["system"].get(val) || !js["system"].is_object()) {
			if (false) { std::cerr << "not find [system]" << std::endl; }
		} else {
			BiotAppSystem o;
			if (json2struct(val, o)) { tst.system = o; }
		}
	}
	{
		simdjson::dom::element val;
		if (simdjson::SUCCESS != js["modules"].get(val) || !js["modules"].is_object()) {
			if (false) { std::cerr << "not find [modules]" << std::endl; }
		} else {
			BiotAppModule o;
			if (json2struct(val, o)) { tst.modules = o; }
		}
	}
	{
		simdjson::dom::element val;
		if (simdjson::SUCCESS != js["product"].get(val) || !js["product"].is_object()) {
			if (false) { std::cerr << "not find [product]" << std::endl; }
		} else {
			BiotAppProduct o;
			if (json2struct(val, o)) { tst.product = o; }
		}
	}

	st = tst;
	return true;
}


}
