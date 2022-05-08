#include "module_subsys.if.h"


namespace biot { 

template <> bool struct2json<BiotAppSubsys>(const BiotAppSubsys &st, nlohmann::json &js) {

	return true;
}

template <> bool json2struct<BiotAppSubsys>(simdjson::dom::element &js, BiotAppSubsys &st) {
	BiotAppSubsys tst;

	st = tst;
	return true;
}


}
