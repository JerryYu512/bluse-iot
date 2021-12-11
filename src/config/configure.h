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
 * @file configure.h
 * @brief 
 * @author wotsen (astralrovers@outlook.com)
 * @version 1.0.0
 * @date 2021-08-15
 * 
 * @copyright MIT License
 * 
 */
#pragma once

namespace ars {

namespace iot {

// 运行时目录
#ifndef IOT_RT_ROOT_PATH
    #define IOT_RT_ROOT_PATH "ars-iot-rt"
#endif // !IOT_RT_ROOT_PATH

// 配置路径
#define IOT_ETC_PATH IOT_RT_ROOT_PATH "/etc/"
// 数据路径
#define IOT_DATA_PATH IOT_RT_ROOT_PATH "/data/"
// 用户路径
#define IOT_USR_PATH IOT_RT_ROOT_PATH "/usr/"

// 日志路径
#define IOT_LOG_PATH IOT_RT_ROOT_PATH "/log/"
// coredump生成路径
#define IOT_COREDUMP_PATH IOT_RT_ROOT_PATH "/coredump/"

// 能力集文件路径
#define IOT_CAPABILITY_FILENAME IOT_RT_ROOT_PATH "/etc/iot_capability.json"
// 配置文件路径
#define IOT_CONFIG_FILENAME IOT_RT_ROOT_PATH "/etc/iot_parameter.json"
#define IOT_CONFIG_PATCH_FILENAME IOT_RT_ROOT_PATH "/etc/iot_parameter_patch.json"
// pid路径
#define IOT_PID_FILENAME "/var/run/ars-iot.pid"

} // namespace iot

} // namespace ars
