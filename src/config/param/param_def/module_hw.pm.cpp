#include "module_hw.if.h"


namespace biot { 

template <> bool struct2json<BiotAppHardware>(const BiotAppHardware &st, nlohmann::json &js) {

	return true;
}

template <> bool json2struct<BiotAppHardware>(simdjson::dom::element &js, BiotAppHardware &st) {
	BiotAppHardware tst;

	st = tst;
	return true;
}


}
