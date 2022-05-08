#include "param_system.if.h"


namespace biot { 

template <> bool struct2json<BiotAppSystem>(const BiotAppSystem &st, nlohmann::json &js) {

	return true;
}

template <> bool json2struct<BiotAppSystem>(simdjson::dom::element &js, BiotAppSystem &st) {
	BiotAppSystem tst;

	st = tst;
	return true;
}


}
