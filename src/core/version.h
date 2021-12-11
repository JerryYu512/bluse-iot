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
 * @file version.h
 * @brief 
 * @author wotsen (astralrovers@outlook.com)
 * @version 1.0.0
 * @date 2021-08-15
 * 
 * @copyright MIT License
 * 
 */
#pragma once

#include <string>

namespace ars {

namespace iot {

/**
 * @brief 应用版本
 * 
 * @return const std::string& 
 */
const std::string app_version(void);

/**
 * @brief 构建版本
 * 
 * @return const std::string 
 */
const std::string app_build_version(void);

/**
 * @brief 应用编译时间
 * 
 * @return const std::string& 
 */
const std::string app_compile_time(void);

/**
 * @brief app识别码，该程序从编译好后的唯一性
 * @details uuid-v4
 * 
 * @return const std::string& 
 */
const std::string app_identifier(void);

/**
 * @brief 发布类型
 * 
 * @return const std::string 
 */
const std::string app_edition(void);

} // namespace iot

} // namespace ars
