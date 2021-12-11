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
 * @file ars_iot_kernel.h
 * @brief 
 * @author wotsen (astralrovers@outlook.com)
 * @version 1.0.0
 * @date 2021-08-01
 * 
 * @copyright MIT License
 * 
 */
#pragma once
#include "ars_iot_boot.h"
#include "ars_iot_extend.h"
#include "MQTTClient.h"
#include "MQTTAsync.h"

namespace ars {

namespace iot {

///< 队列最大大小
#define KERNEL_QUEUE_MAX_SIZE 256

/**
 * @brief 入口状态
 * 
 */
typedef enum {
	kernel_entrance_st_normal,
	kernel_entrance_st_authcode_invalid,
} kernel_entrance_state;

/**
 * @brief 
 * 
 */
typedef enum {
	kernel_run_st_create,
	kernel_run_st_idle,
	kernel_run_st_start,
	kernel_run_st_stop,
	kernel_run_st_close,
} kernel_run_state;

/**
 * @brief 内核网络状态
 * 
 */
typedef enum {
	kernel_net_unredirect,			///< 未重定向
	kernel_net_redirected,			///< 重定向完成
	kernel_net_reged,				///< 已注册
	kernel_net_break,				///< 断开连接
} kernel_net_state;

/**
 * @brief 消息发送回执消息
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
} kernel_sendmsg_ack_t;

///< 内部消息队列
typedef arss::ds::BoundedBlockingQueue<kernel_inner_notice_t, KERNEL_QUEUE_MAX_SIZE> kernel_inner_notice_queue;
typedef arss::ds::BoundedBlockingQueue<kernel_pubmsg_t, KERNEL_QUEUE_MAX_SIZE> kernel_pubmsg_aync_queue;
typedef arss::ds::BoundedBlockingQueue<kernel_submsg_t, KERNEL_QUEUE_MAX_SIZE> kernel_submsg_queue;

/**
 * @brief 内核定义
 * 
 */
typedef struct kernel_s {
	dev_basic_info_t dev_info;											///< 设备信息
	kernel_config_t kernel_conf;										///< 内核配置
	kernel_run_state run_state;											///< 运行状态
	kernel_net_state net_state;											///< 网络状态
	uint32_t extend_cnt;												///< 模块数量
	kernel_module_extend_t extend[ARS_IOT_MODULE_EXTEND_MAX];			///< 模块列表
	// TODO:MQTT
	kernel_submsg_queue submsg_queue;									///< 消息接收队列
	kernel_pubmsg_aync_queue pubmsg_queue;								///< 接受消息队列
	kernel_inner_notice_queue broadcast_queue;							///< 广播队列
	// TODO:threadpool
} kernel_t;

///< 内核初始化
kernel_error_t kernel_init(kernel_t &kernel, dev_basic_info_t &dev_info, kernel_config_t &conf);
kernel_error_t kernel_start(kernel_t &kernel);
kernel_error_t kernel_stop(kernel_t &kernel);
kernel_error_t kernel_finit(kernel_t &kernel);

///< 内核调度
kernel_error_t kernel_core_yield(kernel_t &kernel);

///< 内核用户任务调度
kernel_error_t kernel_core_yield_user(kernel_t &kernel);

///< 网络操作
///< opname: 1.绑定网卡，3.断开重连
kernel_error_t kernel_set_net_option(kernel_t &kernel, int opname, const void *opval, int oplen);

///< 发送消息
kernel_error_t kernel_send_msg(kernel_t &kernel, kernel_pubmsg_t *pubmsg);
kernel_error_t kernel_send_msg_async(kernel_t &kernel, kernel_pubmsg_t *pubmsg);

} // namespace iot

} // namespace ars
