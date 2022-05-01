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
#include "biot_configure.h"

namespace biot {

/**
 * @brief 应用版本
 * 
 * @return const std::string& 
 */
const std::string app_version(void) {
    return BIOT_VERSION;
}

uint32_t app_base_version_date(void) {
    return BIOT_BASE_VERSION;
}

const std::string app_build_date(void) {
    return BIOT_DATE_VERSION;
}

std::string app_base_version(void) {
    char version[64] = "";

    snprintf(version, sizeof(version) - 1, "%s base %d", BIOT_VERSION, BIOT_BASE_VERSION);

    return version;
}

std::string app_std_version(void) {
    char version[64] = "";

    snprintf(version, sizeof(version) - 1, "%s build %.*s", BIOT_VERSION, 8, BIOT_DATE_VERSION);

    return version;
}

/**
 * @brief 应用编译时间
 * 
 * @return const std::string& 
 */
const std::string app_compile_time(void) {
    return BIOT_COMPILE_DATETIME;
}

/**
 * @brief 识别码
 * 
 * @return const std::string& 
 */
const std::string app_identifier(void) {
    return BIOT_UUID;
}

const std::string app_edition(void) {
    return BIOT_EDITION;
}

} // namespace biot
