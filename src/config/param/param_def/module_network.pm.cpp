#include "module_network.if.h"


namespace biot { 

template <> bool struct2json<BiotAppWebServiceParam>(const BiotAppWebServiceParam &st, nlohmann::json &js) {
	{ js["http_port"] = st.http_port; }
	{ js["https_port"] = st.https_port; }
	{ js["http"] = st.http; }
	{ js["https"] = st.https; }
	{ js["root"] = st.root; }
	{ js["connect_max"] = st.connect_max; }

	return true;
}

template <> bool json2struct<BiotAppWebServiceParam>(simdjson::dom::element &js, BiotAppWebServiceParam &st) {
	BiotAppWebServiceParam tst;
	{
		uint64_t val = 0;
		if (simdjson::SUCCESS != js["http_port"].get(val) || !js["http_port"].is_number()) {
			if (false) { std::cerr << "not find [http_port]" << std::endl; }
				tst.http_port = 0;
			} else { tst.http_port = static_cast<uint32_t>(val);
		}
	}
 	{
		uint64_t val = 0;
		if (simdjson::SUCCESS != js["https_port"].get(val) || !js["https_port"].is_number()) {
			if (false) { std::cerr << "not find [https_port]" << std::endl; }
				tst.https_port = 0;
			} else { tst.https_port = static_cast<uint32_t>(val);
		}
	}
 	{
		bool val = false;
		if (simdjson::SUCCESS != js["http"].get(val) || !js["http"].is_bool()) {
			if (false) { std::cerr << "not find [http]" << std::endl; }
			tst.http = false;
		} else { tst.http = val; }
	}
 	{
		bool val = false;
		if (simdjson::SUCCESS != js["https"].get(val) || !js["https"].is_bool()) {
			if (false) { std::cerr << "not find [https]" << std::endl; }
			tst.https = false;
		} else { tst.https = val; }
	}
 	{
		const char* val = nullptr;
		if (simdjson::SUCCESS != js["root"].get(val) || !js["root"].is_string() || !val) {
			if (false) { std::cerr << "not find [root]" << std::endl; }
			const char* d = "";
			if (d) { tst.root = d; }
		} else { tst.root = val; }
	}
 	{
		uint64_t val = 0;
		if (simdjson::SUCCESS != js["connect_max"].get(val) || !js["connect_max"].is_number()) {
			if (false) { std::cerr << "not find [connect_max]" << std::endl; }
				tst.connect_max = 0;
			} else { tst.connect_max = static_cast<uint32_t>(val);
		}
	}
 
	st = tst;
	return true;
}

template <> bool struct2json<BiotAppRtsp>(const BiotAppRtsp &st, nlohmann::json &js) {

	return true;
}

template <> bool json2struct<BiotAppRtsp>(simdjson::dom::element &js, BiotAppRtsp &st) {
	BiotAppRtsp tst;

	st = tst;
	return true;
}

template <> bool struct2json<BiotAppOatppApi>(const BiotAppOatppApi &st, nlohmann::json &js) {
	{ js["port"] = st.port; }
	{ js["ipv4"] = st.ipv4; }
	{ js["body"] = st.body; }

	return true;
}

template <> bool json2struct<BiotAppOatppApi>(simdjson::dom::element &js, BiotAppOatppApi &st) {
	BiotAppOatppApi tst;
	{
		uint64_t val = 0;
		if (simdjson::SUCCESS != js["port"].get(val) || !js["port"].is_number()) {
			if (false) { std::cerr << "not find [port]" << std::endl; }
				tst.port = 0;
			} else { tst.port = static_cast<uint32_t>(val);
		}
	}
 	{
		uint64_t val = 0;
		if (simdjson::SUCCESS != js["ipv4"].get(val) || !js["ipv4"].is_number()) {
			if (false) { std::cerr << "not find [ipv4]" << std::endl; }
				tst.ipv4 = 0;
			} else { tst.ipv4 = static_cast<uint32_t>(val);
		}
	}
 	{
		uint64_t val = 0;
		if (simdjson::SUCCESS != js["body"].get(val) || !js["body"].is_number()) {
			if (false) { std::cerr << "not find [body]" << std::endl; }
				tst.body = static_cast<BiotAppModulePayload>(0);
			} else { tst.body = static_cast<BiotAppModulePayload>(val);
		}
	}
 
	st = tst;
	return true;
}

template <> bool struct2json<BiotAppNetwork>(const BiotAppNetwork &st, nlohmann::json &js) {
	{ for (auto &value: st.lan) { nlohmann::json node; struct2json(value, node); js["lan"].push_back(node); } }
	{ nlohmann::json node; struct2json(st.web, node); js["web"] = node; }
	{ nlohmann::json node; struct2json(st.openapi, node); js["openapi"] = node; }
	{ nlohmann::json node; struct2json(st.cmdapi, node); js["cmdapi"] = node; }

	return true;
}

template <> bool json2struct<BiotAppNetwork>(simdjson::dom::element &js, BiotAppNetwork &st) {
	BiotAppNetwork tst;
	{
		simdjson::dom::array array;
		if (simdjson::SUCCESS != js["lan"].get(array) || !js["lan"].is_array()) {
			if (false) { std::cerr << "not find [lan]" << std::endl; }
		} else {
			size_t len = array.size();
			for (size_t i = 0; i < len; i++) {
				simdjson::dom::element val;
				if (array.at(i).is_object()) {
					if (simdjson::SUCCESS == array.at(i).get(val)) {
						BiotAppLanParam o;
						if (json2struct(val, o)) { tst.lan.push_back(o); }
					}
				}
			}
		}
	}
	{
		simdjson::dom::element val;
		if (simdjson::SUCCESS != js["web"].get(val) || !js["web"].is_object()) {
			if (false) { std::cerr << "not find [web]" << std::endl; }
		} else {
			BiotAppWebServiceParam o;
			if (json2struct(val, o)) { tst.web = o; }
		}
	}
	{
		simdjson::dom::element val;
		if (simdjson::SUCCESS != js["openapi"].get(val) || !js["openapi"].is_object()) {
			if (false) { std::cerr << "not find [openapi]" << std::endl; }
		} else {
			BiotAppOatppApi o;
			if (json2struct(val, o)) { tst.openapi = o; }
		}
	}
	{
		simdjson::dom::element val;
		if (simdjson::SUCCESS != js["cmdapi"].get(val) || !js["cmdapi"].is_object()) {
			if (false) { std::cerr << "not find [cmdapi]" << std::endl; }
		} else {
			BiotAppCmdApi o;
			if (json2struct(val, o)) { tst.cmdapi = o; }
		}
	}

	st = tst;
	return true;
}

template <> bool struct2json<BiotAppLanParam>(const BiotAppLanParam &st, nlohmann::json &js) {
	{ js["type"] = st.type; }
	{ js["cfg_type"] = st.cfg_type; }
	{ js["if_name"] = st.if_name; }
	{ js["mac"] = st.mac; }
	{ js["ipv4"] = st.ipv4; }
	{ js["ipv6"] = st.ipv6; }
	{ js["submask"] = st.submask; }
	{ js["gateway"] = st.gateway; }
	{ js["mtu"] = st.mtu; }
	{ js["dns"] = st.dns; }
	{ js["x1"] = st.x1; }
	{ js["x2"] = st.x2; }
	{ js["x3"] = st.x3; }

	return true;
}

template <> bool json2struct<BiotAppLanParam>(simdjson::dom::element &js, BiotAppLanParam &st) {
	BiotAppLanParam tst;
	{
		uint64_t val = 0;
		if (simdjson::SUCCESS != js["type"].get(val) || !js["type"].is_number()) {
			if (false) { std::cerr << "not find [type]" << std::endl; }
				tst.type = static_cast<NetLanType>(0);
			} else { tst.type = static_cast<NetLanType>(val);
		}
	}
 	{
		uint64_t val = 0;
		if (simdjson::SUCCESS != js["cfg_type"].get(val) || !js["cfg_type"].is_number()) {
			if (false) { std::cerr << "not find [cfg_type]" << std::endl; }
				tst.cfg_type = static_cast<NetCfgType>(0);
			} else { tst.cfg_type = static_cast<NetCfgType>(val);
		}
	}
 	{
		const char* val = nullptr;
		if (simdjson::SUCCESS != js["if_name"].get(val) || !js["if_name"].is_string() || !val) {
			if (false) { std::cerr << "not find [if_name]" << std::endl; }
			const char* d = "";
			if (d) { tst.if_name = d; }
		} else { tst.if_name = val; }
	}
 	{
		const char* val = nullptr;
		if (simdjson::SUCCESS != js["mac"].get(val) || !js["mac"].is_string() || !val) {
			if (false) { std::cerr << "not find [mac]" << std::endl; }
			const char* d = "";
			if (d) { tst.mac = d; }
		} else { tst.mac = val; }
	}
 	{
		const char* val = nullptr;
		if (simdjson::SUCCESS != js["ipv4"].get(val) || !js["ipv4"].is_string() || !val) {
			if (false) { std::cerr << "not find [ipv4]" << std::endl; }
			const char* d = "";
			if (d) { tst.ipv4 = d; }
		} else { tst.ipv4 = val; }
	}
 	{
		const char* val = nullptr;
		if (simdjson::SUCCESS != js["ipv6"].get(val) || !js["ipv6"].is_string() || !val) {
			if (false) { std::cerr << "not find [ipv6]" << std::endl; }
			const char* d = "";
			if (d) { tst.ipv6 = d; }
		} else { tst.ipv6 = val; }
	}
 	{
		const char* val = nullptr;
		if (simdjson::SUCCESS != js["submask"].get(val) || !js["submask"].is_string() || !val) {
			if (false) { std::cerr << "not find [submask]" << std::endl; }
			const char* d = "";
			if (d) { tst.submask = d; }
		} else { tst.submask = val; }
	}
 	{
		const char* val = nullptr;
		if (simdjson::SUCCESS != js["gateway"].get(val) || !js["gateway"].is_string() || !val) {
			if (false) { std::cerr << "not find [gateway]" << std::endl; }
			const char* d = "";
			if (d) { tst.gateway = d; }
		} else { tst.gateway = val; }
	}
 	{
		uint64_t val = 0;
		if (simdjson::SUCCESS != js["mtu"].get(val) || !js["mtu"].is_number()) {
			if (false) { std::cerr << "not find [mtu]" << std::endl; }
				tst.mtu = 1500;
			} else { tst.mtu = static_cast<uint32_t>(val);
		}
	}
 	{
		const char* val = nullptr;
		if (simdjson::SUCCESS != js["dns"].get(val) || !js["dns"].is_string() || !val) {
			if (false) { std::cerr << "not find [dns]" << std::endl; }
			const char* d = "";
			if (d) { tst.dns = d; }
		} else { tst.dns = val; }
	}
 	{
		double val = 0;
		if (simdjson::SUCCESS != js["x1"].get(val) || !js["x1"].is_number()) {
			if (false) { std::cerr << "not find [x1]" << std::endl; }
				tst.x1 = 0.0;
			} else { tst.x1 = static_cast<float>(val);
		}
	}
 	{
		double val = 0;
		if (simdjson::SUCCESS != js["x2"].get(val) || !js["x2"].is_number()) {
			if (false) { std::cerr << "not find [x2]" << std::endl; }
				tst.x2 = 0.0;
			} else { tst.x2 = static_cast<double>(val);
		}
	}
 	{
		bool val = false;
		if (simdjson::SUCCESS != js["x3"].get(val) || !js["x3"].is_bool()) {
			if (false) { std::cerr << "not find [x3]" << std::endl; }
			tst.x3 = false;
		} else { tst.x3 = val; }
	}
 
	st = tst;
	return true;
}

template <> bool struct2json<BiotAppCmdApi>(const BiotAppCmdApi &st, nlohmann::json &js) {
	{ js["port"] = st.port; }
	{ js["ipv4"] = st.ipv4; }
	{ js["trans"] = st.trans; }
	{ js["body"] = st.body; }

	return true;
}

template <> bool json2struct<BiotAppCmdApi>(simdjson::dom::element &js, BiotAppCmdApi &st) {
	BiotAppCmdApi tst;
	{
		uint64_t val = 0;
		if (simdjson::SUCCESS != js["port"].get(val) || !js["port"].is_number()) {
			if (false) { std::cerr << "not find [port]" << std::endl; }
				tst.port = 0;
			} else { tst.port = static_cast<uint32_t>(val);
		}
	}
 	{
		uint64_t val = 0;
		if (simdjson::SUCCESS != js["ipv4"].get(val) || !js["ipv4"].is_number()) {
			if (false) { std::cerr << "not find [ipv4]" << std::endl; }
				tst.ipv4 = 0;
			} else { tst.ipv4 = static_cast<uint32_t>(val);
		}
	}
 	{
		uint64_t val = 0;
		if (simdjson::SUCCESS != js["trans"].get(val) || !js["trans"].is_number()) {
			if (false) { std::cerr << "not find [trans]" << std::endl; }
				tst.trans = static_cast<BiotAppModuleProtocol>(0);
			} else { tst.trans = static_cast<BiotAppModuleProtocol>(val);
		}
	}
 	{
		uint64_t val = 0;
		if (simdjson::SUCCESS != js["body"].get(val) || !js["body"].is_number()) {
			if (false) { std::cerr << "not find [body]" << std::endl; }
				tst.body = static_cast<BiotAppModulePayload>(0);
			} else { tst.body = static_cast<BiotAppModulePayload>(val);
		}
	}
 
	st = tst;
	return true;
}


}
