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
 * @file ars_iot_kernel_def.h
 * @brief
 * @author wotsen (astralrovers@outlook.com)
 * @version 1.0.0
 * @date 2021-07-31
 *
 * @copyright MIT License
 *
 */
#pragma once
#include <stdint.h>
#include "ars_iot_def.h"
#include "ars_iot_kernel_event.h"

namespace ars {

namespace iot {

///< 设备序列号长度
#define ARS_IOT_DEV_SERAIL_LEN 72

///< 设备验证码长度
#define ARS_IOT_DEV_ID_LEN 32

///< 设备验证码长度
#define ARS_IOT_DEV_VERIFICATION_LEN 48

///< 密钥长度
#define ARS_IOT_SECRET_KEY_LEN 32

///< 固件识别码最大长度
#define ARS_IOT_DEV_IDENTIFICATION_LEN 256

///< 内核结构体
typedef struct kernel_s kernel_t;

/**
 * @brief 设备接入模式
 * 
 */
typedef enum {
    ars_iot_dev_access_mode_normal,	///< 正常接入模式
} dev_access_mode_e;

/**
 * @brief 设备认证模式
 * 
 */
typedef enum {
    ars_iot_dev_auth_mode_sap,		///< SAP
    ars_iot_dev_auth_mode_license,	///< License
} dev_auth_mode_e;

/**
 * @brief 设备状态
 * 
 */
typedef enum {
    ars_iot_dev_status_offline,		///< 关机/离线
    ars_iot_dev_status_normal_work,	///< 正常工作
    ars_iot_dev_status_sleep_work,	///< 待机(睡眠)工作模式
} dev_status_e;

/**
 * @brief 内核广播事件
 * 
 */
typedef enum {
    kernel_bt_start,                   ///< 启动
    kernel_bt_stop,                    ///< 停止
    kernel_bt_event,                   ///< 事件
} kernel_broadcast_type;

/**
 * @brief 内部广播消息
 * 
 */
typedef struct {
    kernel_broadcast_type type;     ///< 给广播类型
    kernel_event_msg event_notice;  ///< 事件信息
} kernel_inner_notice_t;

/**
 * @brief 服务器信息
 * 
 */
typedef struct {
    char domain[ARS_IOT_IP_LEN];                    ///< 域名
    char ip[ARS_IOT_IP_LEN];                        ///< ip地址
    uint16_t tcp_port;                              ///< 服务器端口
    int socket;                                     ///< sock
    char session_key[ARS_IOT_SESSION_LEN];          ///< 会话密钥
} kernel_server_info;

/**
 * @brief 密钥
 * 
 */
typedef struct {
    char dev_id[ARS_IOT_DEV_ID_LEN];                            ///< 设备deviceId
    char dev_verification_code[ARS_IOT_DEV_VERIFICATION_LEN];  	///< 设备验证码
    char secret_key[ARS_IOT_SECRET_KEY_LEN];                    ///< 密钥
} dev_key_t;

/**
 * @brief dev key类型
 * 
 */
typedef enum {
    DEV_KEY_DEV_ID,                     ///< 设备deviceID
    DEV_KEY_VERIFICATION_CODE,          ///< 验证码
    DEV_KEY_SECRECT_KEY,                ///< 密钥
} dev_key_type;

/**
 * @brief dev key操作
 * 
 */
typedef enum {
    DEV_KEY_SAVE,                       ///< 保存
    DEV_KEY_LOAD,                       ///< 加载
} dev_key_operate_type;

/**
 * @brief dev key操作回调
 * 
 */
typedef int (*dev_key_operate_cb)(dev_key_type type, dev_key_operate_type op, char *data, uint32_t len);

/**
 * @brief 设备基本信息
 *
 */
typedef struct {
    dev_access_mode_e dev_access_mode;  							        ///< 设备接入模式
    dev_auth_mode_e dev_auth_mode;                      			        ///< 认证模式
    dev_status_e dev_dev_status;  									        ///< 设备状态
    char dev_subserial[ARS_IOT_DEV_SERAIL_LEN];               				///< 设备序列号，唯一
    char dev_verification_code[ARS_IOT_DEV_VERIFICATION_LEN];  				///< 设备验证码
    char dev_serial[ARS_IOT_DEV_SERAIL_LEN];                   				///< 设备长序列号
    char dev_firmware_version[ARS_IOT_NAME_LEN];               				///< 设备固件版本号
    char dev_type[ARS_IOT_NAME_LEN];                           				///< 设备型号
    char dev_type_display[ARS_IOT_NAME_LEN];                   				///< 设备显示型号
    char dev_mac[ARS_IOT_NAME_LEN];                            				///< mac地址
    char dev_nickname[ARS_IOT_NAME_LEN];                       				///< 设备昵称
    char dev_firmware_identification_code[ARS_IOT_DEV_VERIFICATION_LEN];  	///< 设备固件识别码
    uint32_t dev_oem_info;                                                	///< 设备OEM信息
} dev_basic_info_t;

}  // namespace iot

}  // namespace ars
