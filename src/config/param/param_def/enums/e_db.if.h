#pragma once

#include "e_db.pm.h"

#ifndef __ENUM_IF_DECL
#define __ENUM_IF_DECL

#include <stdint.h>
#include <string>
#include <map>

namespace biot { 

template <typename T>
const char* get_enum_str(T e) {
    return "";
}

template <typename T>
const char* get_enum_as_str(T e) {
    return "";
}

template <typename T>
T get_enum_value(const char* str) {
    return T();
}

template <typename T>
bool in_enum_range(T e) {
    return false;
}

}
#endif // __ENUM_IF_DECL


namespace biot { 


template <> const char* get_enum_str<BiotAppDbType>(BiotAppDbType e);
template <> const char* get_enum_as_str<BiotAppDbType>(BiotAppDbType e);
template <> BiotAppDbType get_enum_value<BiotAppDbType>(const char* str);
template <> bool in_enum_range<BiotAppDbType>(BiotAppDbType e);


}
