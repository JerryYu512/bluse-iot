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
 * @file ars_iot_extend.h
 * @brief 
 * @author wotsen (astralrovers@outlook.com)
 * @version 1.0.0
 * @date 2021-08-01
 * 
 * @copyright MIT License
 * 
 */
#pragma once
#include "ars_iot_def.h"

#include <stdint.h>
#include <mutex>
#include <string>
#include "arss/ds/bounde_blocking_queue.h"

#include "ars_iot_kernel_event.h"
#include "ars_iot_error.h"
#include "ars_iot_kernel_def.h"

namespace ars {

namespace iot {

///< 扩展模块名称
#define ARS_IOT_MODULE_EXTEND_NAME_LEN 32

///< 方法类型
#define ARS_IOT_MODULE_EXTEND_METOD_LEN 128

///< 扩展消息
#define ARS_IOT_MODULE_EXTEND_EXT_MSG_LEN 128

///< 最大模块数量
#define ARS_IOT_MODULE_EXTEND_MAX 64

/**
 * @brief 消息qos
 * 
 */
typedef enum {
    QOS_L1,     ///< 最多一次送到
    QOS_L2,     ///< 至少一次送到
    QOS_L3,     ///< 准确一次送到
} kernel_msg_qos;

/**
 * @brief 消息类型
 * 
 */
typedef enum {
    kernel_msg_response,    ///< 响应
    kernel_msg_request,     ///< 请求消息
} kernel_msg_type;

// TODO:消息url的构成

///////////////////////////////////////////////////////////////////
/// /arsapi/iot/serial/model/domain/
/// https://www.cnblogs.com/huang-yc/p/11836877.html
///////////////////////////////////////////////////////////////////

/**
 * @brief 推送消息
 * 
 */
typedef struct {
    kernel_msg_type msg_type;           				///< 消息类型
    kernel_msg_qos qos;                 				///< QOS
    uint32_t seq;                       				///< 消息序列
    unsigned char *msg_ctx;             				///< 消息内容
	uint32_t msg_ctx_len;								///< 消息长度
	char res_id[ARS_IOT_NAME_LEN];						///< 资源id
	char res_type[ARS_IOT_NAME_LEN];					///< 资源类型
	char serail[ARS_IOT_DEV_SERAIL_LEN];				///< 序列号，eg：global，sub_serial
	char module_name[ARS_IOT_MODULE_EXTEND_NAME_LEN];	///< 模块名称，model，ota，basic, storage，media
	char method[ARS_IOT_MODULE_EXTEND_METOD_LEN];		///< 方法类型，eg：event, attribute, service, info, upload/result
	char msg_type_name[ARS_IOT_NAME_LEN];				///< 消息类型，eg：report/query, set_reply, operate_reply
	// char msg_ext[ARS_IOT_MODULE_EXTEND_EXT_MSG_LEN];	///< 扩展内容，model模块中的domainid/identifier
	char compress[ARS_IOT_NAME_LEN];					///< 压缩算法，eg：gzip
	char msg_version[ARS_IOT_VERSION_LEN];				///< 消息版本
} kernel_pubmsg_t;

/**
 * @brief 订阅消息
 * 
 */
typedef struct {
    kernel_msg_type msg_type;           				///< 消息类型
    kernel_msg_qos qos;                 				///< QOS
    uint32_t seq;                       				///< 消息序列
    unsigned char *msg_ctx;             				///< 消息内容
	uint32_t msg_ctx_len;								///< 消息长度
	char res_id[ARS_IOT_NAME_LEN];						///< 资源id
	char res_type[ARS_IOT_NAME_LEN];					///< 资源类型
	char serail[ARS_IOT_DEV_SERAIL_LEN];				///< 序列号，eg：global，sub_serial
	char module_name[ARS_IOT_MODULE_EXTEND_NAME_LEN];	///< 模块名称，model，ota，basic, storage，media
	char method[ARS_IOT_MODULE_EXTEND_METOD_LEN];		///< 方法类型，eg：event, attribute, service, info, upload/result
	char msg_type_name[ARS_IOT_NAME_LEN];				///< 消息类型，eg：report/query, set_reply, operate_reply
	// char msg_ext[ARS_IOT_MODULE_EXTEND_EXT_MSG_LEN];	///< 扩展内容，model模块中的domainid/identifier
	char compress[ARS_IOT_NAME_LEN];					///< 压缩算法，eg：gzip
	char msg_version[ARS_IOT_VERSION_LEN];				///< 消息版本
	void *udata;										///< 用户数据
} kernel_submsg_t;

///< 扩展模块消息路由
typedef void (*kernel_module_extend_msg_route)(kernel_submsg_t *submsg);

/**
 * @brief 消息重定向，只能重定向global消息
 * 
 */
typedef struct {
	char serail[ARS_IOT_DEV_SERAIL_LEN];				///< 序列号，eg：global，sub_serial
	char module_name[ARS_IOT_MODULE_EXTEND_NAME_LEN];	///< 模块名称，model，ota，basic, storage，media
} kernel_submsg_redirect_t;

/**
 * @brief 模块间消息
 * 
 */
typedef struct {
	char to_module_name[ARS_IOT_MODULE_EXTEND_NAME_LEN];	///< 模块名称
	char to_module_version[ARS_IOT_VERSION_LEN];			///< 模块版本号
	char from_module_name[ARS_IOT_MODULE_EXTEND_NAME_LEN];	///< 模块名称
	char from_module_version[ARS_IOT_VERSION_LEN];			///< 模块版本号
	char *req_msg;											///< 请求消息
	uint32_t req_len;										///< 请求消息长度
	char *res_msg;											///< 响应消息
	uint32_t res_len;										///< 响应消息长度
} kernel_module_extend_msg;

/**
 * @brief 内核扩展模块
 * 
 */
typedef struct {
	char module_name[ARS_IOT_MODULE_EXTEND_NAME_LEN];	///< 模块名称
	char module_version[ARS_IOT_VERSION_LEN];			///< 模块版本号
	kernel_module_extend_msg_route route;				///< 模块消息路由
    kernel_event_notice event_notice;					///< 内核消息通知
	void *udata;
} kernel_module_extend_t;

/**
 * @brief 扩展模块载入，非线程安全，需要内核启动前加载
 * 
 * @param kernel 内核句柄
 * @param extend 扩展模块
 * @return kernel_error_t 错误码
 */
kernel_error_t kernel_extend_load_module(kernel_t **kernel, kernel_module_extend_t &extend);

/**
 * @brief 消息发送，非阻塞，线程安全
 * 
 * @param kernel 内核句柄
 * @param pubmsg 消息
 * @return kernel_error_t 错误码
 */
kernel_error_t kernel_extend_pusbmsg(kernel_t *kernel, kernel_pubmsg_t *pubmsg);

/**
 * @brief 模块间通信
 * 
 * @param kernel 
 * @param msg 
 * @return kernel_error_t 
 */
kernel_error_t kernel_extend_send_module_msg(kernel_t *kernel, kernel_module_extend_msg *msg);

/**
 * @brief 获取内核版本
 * 
 * @param kernel 
 * @param version 
 * @return kernel_error_t 
 */
kernel_error_t kernel_extend_version(kernel_t *kernel, std::string &version);

/**
 * @brief 获取设备信息
 * 
 * @param kernel 
 * @param dev_info 
 * @return kernel_error_t 
 */
kernel_error_t kernel_exend_device_info(kernel_t *kernel, dev_basic_info_t &dev_info);

///< 服务器信息
kernel_error_t kernel_exend_server_info(kernel_t *kernel, kernel_server_info &server_info);

///< key
kernel_error_t kernel_exend_dev_key(kernel_t *kernel, dev_key_t &key);

///< 消息重定向注册重定向
kernel_error_t kernel_extend_register_redirect(kernel_t *kernel, kernel_submsg_redirect_t &redirect_info);

// TODO:查询可重定向的消息

} // namespace iot

} // namespace ars
