#include "param_basic.if.h"


namespace biot { 

template <> bool struct2json<BiotAppUsers>(const BiotAppUsers &st, nlohmann::json &js) {
	{ for (auto &value: st.access_users) { nlohmann::json node; struct2json(value, node); js["access_users"].push_back(node); } }

	return true;
}

template <> bool json2struct<BiotAppUsers>(simdjson::dom::element &js, BiotAppUsers &st) {
	BiotAppUsers tst;
	{
		simdjson::dom::array array;
		if (simdjson::SUCCESS != js["access_users"].get(array) || !js["access_users"].is_array()) {
			if (false) { std::cerr << "not find [access_users]" << std::endl; }
		} else {
			size_t len = array.size();
			for (size_t i = 0; i < len; i++) {
				simdjson::dom::element val;
				if (array.at(i).is_object()) {
					if (simdjson::SUCCESS == array.at(i).get(val)) {
						BiotAppAccessUser o;
						if (json2struct(val, o)) { tst.access_users.push_back(o); }
					}
				}
			}
		}
	}

	st = tst;
	return true;
}

template <> bool struct2json<BiotAppBasicParam>(const BiotAppBasicParam &st, nlohmann::json &js) {
	{ js["appmode"] = st.appmode; }
	{ nlohmann::json node; struct2json(st.user, node); js["user"] = node; }

	return true;
}

template <> bool json2struct<BiotAppBasicParam>(simdjson::dom::element &js, BiotAppBasicParam &st) {
	BiotAppBasicParam tst;
	{
		uint64_t val = 0;
		if (simdjson::SUCCESS != js["appmode"].get(val) || !js["appmode"].is_number()) {
			if (false) { std::cerr << "not find [appmode]" << std::endl; }
				tst.appmode = static_cast<EBiotAppMode>(0);
			} else { tst.appmode = static_cast<EBiotAppMode>(val);
		}
	}
 	{
		simdjson::dom::element val;
		if (simdjson::SUCCESS != js["user"].get(val) || !js["user"].is_object()) {
			if (false) { std::cerr << "not find [user]" << std::endl; }
		} else {
			BiotAppUsers o;
			if (json2struct(val, o)) { tst.user = o; }
		}
	}

	st = tst;
	return true;
}

template <> bool struct2json<BiotAppAccessUser>(const BiotAppAccessUser &st, nlohmann::json &js) {
	{ js["name"] = st.name; }
	{ js["passwd"] = st.passwd; }
	{ js["expired"] = st.expired; }
	{ js["permission"] = st.permission; }
	{ js["allowlist"] = st.allowlist; }
	{ js["email"] = st.email; }
	{ js["phone"] = st.phone; }
	{ js["github"] = st.github; }

	return true;
}

template <> bool json2struct<BiotAppAccessUser>(simdjson::dom::element &js, BiotAppAccessUser &st) {
	BiotAppAccessUser tst;
	{
		const char* val = nullptr;
		if (simdjson::SUCCESS != js["name"].get(val) || !js["name"].is_string() || !val) {
			if (false) { std::cerr << "not find [name]" << std::endl; }
			const char* d = "";
			if (d) { tst.name = d; }
		} else { tst.name = val; }
	}
 	{
		const char* val = nullptr;
		if (simdjson::SUCCESS != js["passwd"].get(val) || !js["passwd"].is_string() || !val) {
			if (false) { std::cerr << "not find [passwd]" << std::endl; }
			const char* d = "";
			if (d) { tst.passwd = d; }
		} else { tst.passwd = val; }
	}
 	{
		uint64_t val = 0;
		if (simdjson::SUCCESS != js["expired"].get(val) || !js["expired"].is_number()) {
			if (false) { std::cerr << "not find [expired]" << std::endl; }
				tst.expired = 0;
			} else { tst.expired = static_cast<uint64_t>(val);
		}
	}
 	{
		const char* val = nullptr;
		if (simdjson::SUCCESS != js["permission"].get(val) || !js["permission"].is_string() || !val) {
			if (false) { std::cerr << "not find [permission]" << std::endl; }
			const char* d = "";
			if (d) { tst.permission = d; }
		} else { tst.permission = val; }
	}
 	{
		bool val = false;
		if (simdjson::SUCCESS != js["allowlist"].get(val) || !js["allowlist"].is_bool()) {
			if (false) { std::cerr << "not find [allowlist]" << std::endl; }
			tst.allowlist = false;
		} else { tst.allowlist = val; }
	}
 	{
		const char* val = nullptr;
		if (simdjson::SUCCESS != js["email"].get(val) || !js["email"].is_string() || !val) {
			if (false) { std::cerr << "not find [email]" << std::endl; }
			const char* d = "";
			if (d) { tst.email = d; }
		} else { tst.email = val; }
	}
 	{
		const char* val = nullptr;
		if (simdjson::SUCCESS != js["phone"].get(val) || !js["phone"].is_string() || !val) {
			if (false) { std::cerr << "not find [phone]" << std::endl; }
			const char* d = "";
			if (d) { tst.phone = d; }
		} else { tst.phone = val; }
	}
 	{
		const char* val = nullptr;
		if (simdjson::SUCCESS != js["github"].get(val) || !js["github"].is_string() || !val) {
			if (false) { std::cerr << "not find [github]" << std::endl; }
			const char* d = "";
			if (d) { tst.github = d; }
		} else { tst.github = val; }
	}
 
	st = tst;
	return true;
}


}
