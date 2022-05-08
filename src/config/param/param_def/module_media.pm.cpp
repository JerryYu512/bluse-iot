#include "module_media.if.h"


namespace biot { 

template <> bool struct2json<BiotAppMedia>(const BiotAppMedia &st, nlohmann::json &js) {

	return true;
}

template <> bool json2struct<BiotAppMedia>(simdjson::dom::element &js, BiotAppMedia &st) {
	BiotAppMedia tst;

	st = tst;
	return true;
}


}
