#include "module_device.if.h"


namespace biot { 

template <> bool struct2json<BiotAppDevice>(const BiotAppDevice &st, nlohmann::json &js) {

	return true;
}

template <> bool json2struct<BiotAppDevice>(simdjson::dom::element &js, BiotAppDevice &st) {
	BiotAppDevice tst;

	st = tst;
	return true;
}


}
