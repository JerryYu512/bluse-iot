#pragma once

#include "param_basic.pm.h"


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

template <> bool json2struct<BiotAppUsers>(simdjson::dom::element &js, BiotAppUsers &st);
template <> bool struct2json<BiotAppUsers>(const BiotAppUsers &st, nlohmann::json &js);
template <> bool json2struct<BiotAppBasicParam>(simdjson::dom::element &js, BiotAppBasicParam &st);
template <> bool struct2json<BiotAppBasicParam>(const BiotAppBasicParam &st, nlohmann::json &js);
template <> bool json2struct<BiotAppAccessUser>(simdjson::dom::element &js, BiotAppAccessUser &st);
template <> bool struct2json<BiotAppAccessUser>(const BiotAppAccessUser &st, nlohmann::json &js);

}
