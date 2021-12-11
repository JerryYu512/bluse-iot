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
 * @file module.h
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
#include <stdint.h>
#include <memory>
#include <functional>

namespace ars {

namespace iot {

// 模块状态
typedef enum {
    E_MODULE_ST_STOP = 0,       ///< 停止
    E_MODULE_ST_RUNNING = 1,    ///< 运行中
    E_MODULE_ST_BAD = 2,        ///< 异常
} module_st_t;

// 模块权限
typedef enum {
    E_MODULE_PER_NO = 0,        ///< 无权限
    E_MODULE_PER_VIEWER = 1,    ///< 可视权限
    E_MODULE_PER_USER = 2,      ///< 普通权限
    E_MODULE_PER_ADMIN = 3,     ///< 超级权限
} module_permission_t;

// 模块分组
typedef enum {
    E_MODULE_GROUP_CORE,     	///< 系统核心模块
    E_MODULE_GROUP_BASIC,    	///< 基础组件
    E_MODULE_GROUP_SOURCE,  	///< 资源组件
    E_MODULE_GROUP_SERVICE,  	///< 服务组件
    E_MODULE_GROUP_OPENAPI,  	///< 开放API组件
} module_group_t;

// 模块分类
typedef enum {
    E_MODULE_TYPE_HW,      	///< 硬件
    E_MODULE_TYPE_OS,      	///< 系统
    E_MODULE_TYPE_DATA,     ///< 数据库
    E_MODULE_TYPE_STORAGE,  ///< 存储
    E_MODULE_TYPE_NET,      ///< 网络
    E_MODULE_TYPE_APP,      ///< 应用
} module_type_t;

using module_identi_t = std::string;

/**
 * @brief 模块消息类型
 * 
 */
typedef enum {
    module_msg_req,     ///< 请求消息
    module_msg_res,     ///< 响应消息
} module_message_type;

/**
 * @brief 同步短连接消息
 * 
 */
typedef struct {
    std::string from;       ///< 来源模块
    std::string to;         ///< 目的模块
    module_message_type type;   ///< 消息类型
    char *msg;              ///< 消息
    size_t msg_len;         ///< 消息长度
} module_sync_message_t;

/**
 * @brief 异步消息
 * 
 */
typedef struct {
    std::string from;       ///< 来源模块
    std::string to;         ///< 目的模块
    module_message_type type;   ///< 消息类型
    char *msg;              ///< 消息
    size_t msg_len;         ///< 消息长度
    void *user_data;        ///< 用户数据
} module_async_message_t;

typedef struct {
    std::string peer;
    std::string local;
    size_t recv_buf_size;
    size_t send_buf_size;
    bool sync;
    time_t send_timeout;
    time_t recv_timeout;
} module_stream_message_opt_t;

class ModuleStreamMessage {
public:
    ModuleStreamMessage();
    ~ModuleStreamMessage();

    ///< 连接
    int connect(const std::string &peer, const std::string &local);
    ///< 关闭
    void close(void);
    ///< 是否有效
    bool invalid(void);
    ///< 数据发送
    int send(void *data, size_t len);
    int send(const std::string &data);
    ///< 数据接收
    int recv(void *data, size_t len);
    int recv(std::string &data);

private:
    bool connected_;        ///< 是否已经连接
    std::string peer_;      ///< 对端地址
    std::string local_;     ///< 本地地址
};

class ModuleStreamMessageConn {
public:
    ModuleStreamMessageConn();
    ~ModuleStreamMessageConn();
};

///< 同步发送接口类型
using module_message_sync_send_t = std::function<int(module_sync_message_t *, module_sync_message_t *)>;
///< 异步接口发送类型
using module_message_async_send_t = std::function<int(module_async_message_t *)>;
///< 获取模块内核版本号
using module_get_kernel_version_t = std::function<std::string()>;

// TODO:接收端与发送端使用两个管道，发送缓冲区->接收缓冲区
///< 创建连接
using module_stream_message_conn_create_t = std::function<int(const module_stream_message_opt_t &opt, ModuleStreamMessageConn **)>;
///< 发送
using module_stream_message_send_t = std::function<int(ModuleStreamMessageConn*, void *data, size_t len, time_t wait=0)>;
///< 接收
using module_stream_message_recv_t = std::function<int(ModuleStreamMessageConn*, void *data, size_t len, time_t wait=0)>;
///< 关闭连接
using module_stream_message_close_t = std::function<void(ModuleStreamMessageConn**)>;
///< 连接状态
using module_stream_message_status_t = std::function<int(ModuleStreamMessageConn*)>;
///< 对端
using module_stream_message_peer_t = std::function<int(ModuleStreamMessageConn*, std::string &peer)>;
///< 本地
using module_stream_message_local_t = std::function<int(ModuleStreamMessageConn*, std::string &local)>;
// TODO:设置获取选项
// TODO:设置获取阻塞
// TODO:获取是否可读
// TODO:获取是否可发送
// TODO:获取recv缓冲区大小
// TODO:设置recv缓冲区大小

/**
 * @brief 流式消息接口
 * 
 */
typedef struct {
    module_stream_message_conn_create_t connet;     ///< 连接
    module_stream_message_close_t close;            ///< 关闭
    module_stream_message_send_t send;              ///< 发送
    module_stream_message_recv_t recv;              ///< 接收
    module_stream_message_status_t status;          ///< 连接状态
    module_stream_message_peer_t peer;              ///< 对端地址
    module_stream_message_local_t local;            ///< 本地地址
} module_stream_message_interface_t;

/**
 * @brief 模块接口
 * 
 */
typedef struct {
    module_message_sync_send_t sync_send;       ///< 同步发送
    module_message_async_send_t async_send;     ///< 异步发送
    module_get_kernel_version_t kernel_version; ///< 内核版本
} module_interface_t;

/**
 * @brief 模块基本信息
 * 
 */
typedef struct {
    std::string name;           ///< 模块名称
    std::string desc;           ///< 模块描述
    std::string version;        ///< 模块版本
    bool enable;                ///< 使能
    module_identi_t identifier;         ///< 标识，由初始加载时进行分配一个，模块自身不用去填写
    module_type_t type;                 ///< 模块类别
    module_group_t group;               ///< 分组
    module_permission_t permission;     ///< 权限
} module_base_info_t;

// 模块定义
class IModule {
public:
    IModule(const module_base_info_t &info) : info_(info) {}
    virtual ~IModule() {}

    virtual bool init(void *param) = 0;
    virtual bool start(void *param) = 0;
    virtual bool stop(void *param) = 0;
    virtual bool exit(void *param) = 0;
    virtual void message_proc(void *data, size_t len) = 0;
    // 不能阻塞
    virtual void stream_message_proc(ModuleStreamMessageConn *conn) = 0;

    virtual module_st_t status(void) {
        return st_;
    }

    virtual void set_status(module_st_t st) {
        st_ = st;
    }

    virtual module_base_info_t module_info(void) {
        return info_;
    }

    virtual void set_identifier(const std::string &identi) {
        info_.identifier = identi;
    }

public:
    module_base_info_t info_;   	///< 模块基本信息
    module_st_t st_;               	///< 模块状态
};

// 定义模块引用接口
#define DEFINE_IOT_MODULE_REF(name) std::shared_ptr<ars::iot::IModule> _arsiot_##name##_module_object_ref(void)
// 模块引用
#define IOT_MODULE_REF(name) ars::iot::_arsiot_##name##_module_object_ref()

} // namespace iot

} // namespace ars
