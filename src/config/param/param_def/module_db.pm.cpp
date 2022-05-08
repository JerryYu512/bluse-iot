#include "module_db.if.h"


namespace biot { 

template <> bool struct2json<BiotAppDbLocal>(const BiotAppDbLocal &st, nlohmann::json &js) {
	{ js["dbtype"] = st.dbtype; }

	return true;
}

template <> bool json2struct<BiotAppDbLocal>(simdjson::dom::element &js, BiotAppDbLocal &st) {
	BiotAppDbLocal tst;
	{
		uint64_t val = 0;
		if (simdjson::SUCCESS != js["dbtype"].get(val) || !js["dbtype"].is_number()) {
			if (false) { std::cerr << "not find [dbtype]" << std::endl; }
				tst.dbtype = static_cast<BiotAppDbType>(0);
			} else { tst.dbtype = static_cast<BiotAppDbType>(val);
		}
	}
 
	st = tst;
	return true;
}

template <> bool struct2json<BiotAppDb>(const BiotAppDb &st, nlohmann::json &js) {
	{ nlohmann::json node; struct2json(st.localdb, node); js["localdb"] = node; }

	return true;
}

template <> bool json2struct<BiotAppDb>(simdjson::dom::element &js, BiotAppDb &st) {
	BiotAppDb tst;
	{
		simdjson::dom::element val;
		if (simdjson::SUCCESS != js["localdb"].get(val) || !js["localdb"].is_object()) {
			if (false) { std::cerr << "not find [localdb]" << std::endl; }
		} else {
			BiotAppDbLocal o;
			if (json2struct(val, o)) { tst.localdb = o; }
		}
	}

	st = tst;
	return true;
}


}
