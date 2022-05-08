// 配置参数根节点.
#pragma once

#include "param.pm.h"



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

template <> bool json2struct<BiotAppParam>(simdjson::dom::element &js, BiotAppParam &st);
template <> bool struct2json<BiotAppParam>(const BiotAppParam &st, nlohmann::json &js);

}
