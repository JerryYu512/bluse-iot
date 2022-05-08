#include "param_product.if.h"


namespace biot { 

template <> bool struct2json<BiotAppProduct>(const BiotAppProduct &st, nlohmann::json &js) {

	return true;
}

template <> bool json2struct<BiotAppProduct>(simdjson::dom::element &js, BiotAppProduct &st) {
	BiotAppProduct tst;

	st = tst;
	return true;
}


}
