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

namespace biot {

#ifndef SOFT_VERSION
    #define SOFT_VERSION "0.0.0"
#endif

#ifndef BUILD_VERSION
    #define BUILD_VERSION "202101010000"
#endif

#ifndef APP_COMPILE_TIME
    #define APP_COMPILE_TIME "Monday 2021-01-01 00:00:00 +0800"
#endif

#ifndef APP_UUID
    #define APP_UUID "00000000-0000-0000-0000-000000000000"
#endif

// 主版本号
// static uint32_t major_verson = 1;
// 次版本号
// static uint32_t minor_verson = 0;
// 发布版本号
// static uint32_t release_verson = 0;
// 发布版本日期，该日期为该版本的开始开发日期
static uint32_t base_version_date = 22020402;

/**
 * @brief 应用版本
 * 
 * @return const std::string& 
 */
const std::string app_version(void) {
    return SOFT_VERSION;
}

uint32_t app_base_version_date(void) {
    return base_version_date;
}

const std::string app_build_date(void) {
    return BUILD_VERSION;
}

std::string app_base_version(void) {
    char version[64] = "";

    snprintf(version, sizeof(version) - 1, "%s base %d", SOFT_VERSION, base_version_date);

    return version;
}

std::string app_std_version(void) {
    char version[64] = "";

    snprintf(version, sizeof(version) - 1, "%s build %.*s", SOFT_VERSION, 8, BUILD_VERSION);

    return version;
}

/**
 * @brief 应用编译时间
 * 
 * @return const std::string& 
 */
const std::string app_compile_time(void) {
    return APP_COMPILE_TIME;
}

/**
 * @brief 识别码
 * 
 * @return const std::string& 
 */
const std::string app_identifier(void) {
    return APP_UUID;
}

const std::string app_edition(void) {
#ifdef DEBUG
    return "debug";
#endif

    return "release";
}

} // namespace biot
