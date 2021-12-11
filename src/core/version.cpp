/**
 * MIT License
 * 
 * Copyright © 2021 <wotsen>.
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software
 * and associated documentation files (the “Software”), to deal in the Software without
 * restriction, including without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the
 * 
 * The above copyright notice and this permission notice shall be included in all copies or
 * substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
 * BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 * 
 * @file versoin.cpp
 * @brief 
 * @author wotsen (astralrovers@outlook.com)
 * @version 1.0.0
 * @date 2021-08-15
 * 
 * @copyright MIT License
 * 
 */
#include "version.h"

namespace ars {

namespace iot {

/**
 * @brief 应用版本
 * 
 * @return const std::string& 
 */
const std::string app_version(void) {
#ifndef SOFT_VERSION
    #define SOFT_VERSION "0.0.0"
#endif

    return SOFT_VERSION;
}

const std::string app_build_version(void) {
#ifndef BUILD_VERSION
    #define BUILD_VERSION "202101010000"
#endif

    return BUILD_VERSION;
}

/**
 * @brief 应用编译时间
 * 
 * @return const std::string& 
 */
const std::string app_compile_time(void) {
#ifndef APP_COMPILE_TIME
    #define APP_COMPILE_TIME "Monday 2021-01-01 00:00:00 +0800"
#endif
    return APP_COMPILE_TIME;
}

/**
 * @brief 识别码
 * 
 * @return const std::string& 
 */
const std::string app_identifier(void) {
#ifndef APP_UUID
    #define APP_UUID "00000000-0000-0000-0000-000000000000"
#endif

    return APP_UUID;
}

const std::string app_edition(void) {
#ifdef DEBUG
    return "debug";
#endif

    return "release";
}

} // namespace iot

} // namespace ars
