#pragma once

#include "module_db.pm.h"


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

template <> bool json2struct<BiotAppDbLocal>(simdjson::dom::element &js, BiotAppDbLocal &st);
template <> bool struct2json<BiotAppDbLocal>(const BiotAppDbLocal &st, nlohmann::json &js);
template <> bool json2struct<BiotAppDb>(simdjson::dom::element &js, BiotAppDb &st);
template <> bool struct2json<BiotAppDb>(const BiotAppDb &st, nlohmann::json &js);

}
