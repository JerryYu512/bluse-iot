#pragma once
#include <stdint.h>
#include <string>
#include <map>

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