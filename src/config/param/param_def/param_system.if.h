#pragma once

#include "param_system.pm.h"


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

template <> bool json2struct<BiotAppSystem>(simdjson::dom::element &js, BiotAppSystem &st);
template <> bool struct2json<BiotAppSystem>(const BiotAppSystem &st, nlohmann::json &js);

}
