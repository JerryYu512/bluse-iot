#pragma once

#include "module_network.pm.h"


#ifndef __STRUCT_IF_DECL
#define __STRUCT_IF_DECL

#include "simdjson.h"
#include "hv/json.hpp"

namespace biot { 

template <typename T>
bool json2struct(simdjson::dom::element &js, T &st) {
    return false;
}

template <typename T>
bool struct2json(const T &st, nlohmann::json &js) {
    return false;
}
}

#endif // __STRUCT_IF_DECL


namespace biot { 

template <> bool json2struct<BiotAppWebServiceParam>(simdjson::dom::element &js, BiotAppWebServiceParam &st);
template <> bool struct2json<BiotAppWebServiceParam>(const BiotAppWebServiceParam &st, nlohmann::json &js);
template <> bool json2struct<BiotAppRtsp>(simdjson::dom::element &js, BiotAppRtsp &st);
template <> bool struct2json<BiotAppRtsp>(const BiotAppRtsp &st, nlohmann::json &js);
template <> bool json2struct<BiotAppOatppApi>(simdjson::dom::element &js, BiotAppOatppApi &st);
template <> bool struct2json<BiotAppOatppApi>(const BiotAppOatppApi &st, nlohmann::json &js);
template <> bool json2struct<BiotAppNetwork>(simdjson::dom::element &js, BiotAppNetwork &st);
template <> bool struct2json<BiotAppNetwork>(const BiotAppNetwork &st, nlohmann::json &js);
template <> bool json2struct<BiotAppLanParam>(simdjson::dom::element &js, BiotAppLanParam &st);
template <> bool struct2json<BiotAppLanParam>(const BiotAppLanParam &st, nlohmann::json &js);
template <> bool json2struct<BiotAppCmdApi>(simdjson::dom::element &js, BiotAppCmdApi &st);
template <> bool struct2json<BiotAppCmdApi>(const BiotAppCmdApi &st, nlohmann::json &js);

}
