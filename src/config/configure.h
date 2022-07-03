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

namespace biot {

/////////////////////////////////////////////////////////////
/// !!! 系统基础配置
/////////////////////////////////////////////////////////////

// 运行时目录
#ifndef BIOT_RT_ROOT_PATH
    #define BIOT_RT_ROOT_PATH "bluse-iot-rt"
#endif // !BIOT_RT_ROOT_PATH

// 配置路径
#define BIOT_ETC_PATH BIOT_RT_ROOT_PATH "/etc/"
// 数据路径
#define BIOT_DATA_PATH BIOT_RT_ROOT_PATH "/data/"
// 用户路径
#define BIOT_USR_PATH BIOT_RT_ROOT_PATH "/usr/"

// 日志路径
#define BIOT_LOG_PATH BIOT_RT_ROOT_PATH "/log/"
// 日志文件单个最大大小 20M
#define BIOT_LOG_MAX_FILESIZE (20 * 1024 * 1024)
// 日志文件循环个数
#define BIOT_LOG_FILE_MAX_NUM 64
// coredump生成路径
#define BIOT_COREDUMP_PATH BIOT_RT_ROOT_PATH "/coredump/"

#define BIOT_SEC_PARAM_FILENAME BIOT_RT_ROOT_PATH "/etc/biot_sec_param.bin"
// 能力集文件路径
#define BIOT_CAPABILITY_FILENAME BIOT_RT_ROOT_PATH "/etc/biot_capability.bin"
// 配置文件路径
#define BIOT_CONFIG_FILENAME BIOT_RT_ROOT_PATH "/etc/biot_parameter.bin"
#define BIOT_CONFIG_BACKUP_FILENAME BIOT_RT_ROOT_PATH "/etc/biot_parameter_backup.bin"
#define BIOT_CONFIG_PATCH_FILENAME BIOT_RT_ROOT_PATH "/etc/biot_parameter_patch.bin"
// pid路径
#define BIOT_PID_FILENAME "/var/run/bluse-iot.pid"

/////////////////////////////////////////////////////////////
/// !!! 模块配置
/////////////////////////////////////////////////////////////

/// !!! 网络
#define BIOT_NET_PORT_START 9000
// web服务器
#define BIOT_WEBAPP_NAME "BiotWebApp"
#define BIOT_WEBAPP_ROOT_PATH BIOT_RT_ROOT_PATH "/webapp/"
#define BIOT_WEBAPP_DEFAULT_IP "0.0.0.0"
#define BIOT_WEBAPP_DEFAULT_PORT 9000
#define BIOT_WEBAPP_DEFAULT_AUTH "Basic"
#define BIOT_WEBAPP_DEFAULT_BASIC_AUTH_REALM "BiotRealm"
#define BIOT_WEBAPP_DEFAULT_USER_NAME "admin"
#define BIOT_WEBAPP_DEFAULT_USER_PASSWD "abc12345"

} // namespace biot
