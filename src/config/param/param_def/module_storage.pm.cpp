#include "module_storage.if.h"


namespace biot { 

template <> bool struct2json<BiotAppStorage>(const BiotAppStorage &st, nlohmann::json &js) {

	return true;
}

template <> bool json2struct<BiotAppStorage>(simdjson::dom::element &js, BiotAppStorage &st) {
	BiotAppStorage tst;

	st = tst;
	return true;
}


}
