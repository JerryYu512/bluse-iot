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
 * @file ars_iot_boot.h
 * @brief 
 * @author wotsen (astralrovers@outlook.com)
 * @version 1.0.0
 * @date 2021-08-04
 * 
 * @copyright MIT License
 * 
 */
#pragma once
#include "ars_iot_kernel_def.h"
#include "ars_iot_kernel_event.h"
#include "ars_iot_kernel_log.h"
#include "ars_iot_error.h"

namespace ars {

namespace iot {

///< 内核回调接口
typedef struct {
    kernel_event_notice event_notice;
    kernel_log_cb log;
	dev_key_operate_cb dev_key;
	// TODO:SSL
} kenerl_callback;

/**
 * @brief 内核配置
 * 
 */
typedef struct {
    char srv_host[ARS_IOT_NAME_LEN];                ///< 服务器域名
    int16_t srv_port;                               ///< 服务器端口
    kenerl_callback cb;                             ///< 回调
    char devinfo_path[128];                         ///< 设备信息文件路径，json格式
    uint32_t msg_max_size;                          ///< 单条消息最大大小，最小/默认16k，最大支持256k
    uint8_t msg_compress;                           ///< 报文压缩使能
    void *ud;                                       ///< 用户数据
} kernel_config_t;

/**
 * @brief 初始化
 * 
 * @param conf 配置
 * @return kernel_error_t 
 */
kernel_error_t kernel_boot_init(kernel_config_t &conf);

/**
 * @brief 启动
 * 
 * @return kernel_error_t 
 */
kernel_error_t kernel_boot_start(void);

/**
 * @brief 停止
 * 
 * @return kernel_error_t 
 */
kernel_error_t kernel_boot_stop(void);

/**
 * @brief 停止
 * 
 * @return kernel_error_t 
 */
kernel_error_t kernel_boot_finit(void);

} // namespace iot

} // namespace ars
