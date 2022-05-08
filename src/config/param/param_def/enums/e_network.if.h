#pragma once

#include "e_network.pm.h"

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


template <> const char* get_enum_str<BiotAppModulePayload>(BiotAppModulePayload e);
template <> const char* get_enum_as_str<BiotAppModulePayload>(BiotAppModulePayload e);
template <> BiotAppModulePayload get_enum_value<BiotAppModulePayload>(const char* str);
template <> bool in_enum_range<BiotAppModulePayload>(BiotAppModulePayload e);


template <> const char* get_enum_str<BiotAppModuleProtocol>(BiotAppModuleProtocol e);
template <> const char* get_enum_as_str<BiotAppModuleProtocol>(BiotAppModuleProtocol e);
template <> BiotAppModuleProtocol get_enum_value<BiotAppModuleProtocol>(const char* str);
template <> bool in_enum_range<BiotAppModuleProtocol>(BiotAppModuleProtocol e);


template <> const char* get_enum_str<NetCfgType>(NetCfgType e);
template <> const char* get_enum_as_str<NetCfgType>(NetCfgType e);
template <> NetCfgType get_enum_value<NetCfgType>(const char* str);
template <> bool in_enum_range<NetCfgType>(NetCfgType e);


template <> const char* get_enum_str<NetIfRate>(NetIfRate e);
template <> const char* get_enum_as_str<NetIfRate>(NetIfRate e);
template <> NetIfRate get_enum_value<NetIfRate>(const char* str);
template <> bool in_enum_range<NetIfRate>(NetIfRate e);


template <> const char* get_enum_str<NetLanType>(NetLanType e);
template <> const char* get_enum_as_str<NetLanType>(NetLanType e);
template <> NetLanType get_enum_value<NetLanType>(const char* str);
template <> bool in_enum_range<NetLanType>(NetLanType e);


template <> const char* get_enum_str<WireLessIfMode>(WireLessIfMode e);
template <> const char* get_enum_as_str<WireLessIfMode>(WireLessIfMode e);
template <> WireLessIfMode get_enum_value<WireLessIfMode>(const char* str);
template <> bool in_enum_range<WireLessIfMode>(WireLessIfMode e);


template <> const char* get_enum_str<WireLessSecMode>(WireLessSecMode e);
template <> const char* get_enum_as_str<WireLessSecMode>(WireLessSecMode e);
template <> WireLessSecMode get_enum_value<WireLessSecMode>(const char* str);
template <> bool in_enum_range<WireLessSecMode>(WireLessSecMode e);


template <> const char* get_enum_str<WireLessWepAuthType>(WireLessWepAuthType e);
template <> const char* get_enum_as_str<WireLessWepAuthType>(WireLessWepAuthType e);
template <> WireLessWepAuthType get_enum_value<WireLessWepAuthType>(const char* str);
template <> bool in_enum_range<WireLessWepAuthType>(WireLessWepAuthType e);


template <> const char* get_enum_str<WireLessWepKeyLen>(WireLessWepKeyLen e);
template <> const char* get_enum_as_str<WireLessWepKeyLen>(WireLessWepKeyLen e);
template <> WireLessWepKeyLen get_enum_value<WireLessWepKeyLen>(const char* str);
template <> bool in_enum_range<WireLessWepKeyLen>(WireLessWepKeyLen e);


template <> const char* get_enum_str<WireLessWepKeyType>(WireLessWepKeyType e);
template <> const char* get_enum_as_str<WireLessWepKeyType>(WireLessWepKeyType e);
template <> WireLessWepKeyType get_enum_value<WireLessWepKeyType>(const char* str);
template <> bool in_enum_range<WireLessWepKeyType>(WireLessWepKeyType e);


template <> const char* get_enum_str<WireLessWorkMode>(WireLessWorkMode e);
template <> const char* get_enum_as_str<WireLessWorkMode>(WireLessWorkMode e);
template <> WireLessWorkMode get_enum_value<WireLessWorkMode>(const char* str);
template <> bool in_enum_range<WireLessWorkMode>(WireLessWorkMode e);


template <> const char* get_enum_str<WireLessWpaEncryptType>(WireLessWpaEncryptType e);
template <> const char* get_enum_as_str<WireLessWpaEncryptType>(WireLessWpaEncryptType e);
template <> WireLessWpaEncryptType get_enum_value<WireLessWpaEncryptType>(const char* str);
template <> bool in_enum_range<WireLessWpaEncryptType>(WireLessWpaEncryptType e);


}
