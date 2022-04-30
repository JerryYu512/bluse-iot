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
 * @file parameter.h
 * @brief 
 * @author wotsen (astralrovers@outlook.com)
 * @version 1.0.0
 * @date 2021-08-15
 * 
 * @copyright MIT License
 * 
 */
#pragma once
#include "hv/json.hpp"
#include "hv/hmutex.h"
#include "hv/singleton.h"

namespace biot {

using param_json_t = nlohmann::json;

/**
 * @brief 参数配置
 *
 */
class Parameter {
public:
    /**
     * @brief 配置初始化
     *
     * @param path 配置文件路径
     */
    static void init(const std::string &path);

    /**
     * @brief Get the Instance object
     *
     * @param path 配置文件路径，只需要第一次调用传入
     * @return Parameter& 配置参数对象应用
     */
    static Parameter &get_instance(const std::string &path = "");

    /**
     * @brief 获取json参数引用
     *
     * @return param_json_t&
     */
    param_json_t &parameter_ref(void);

    /**
     * @brief 固化到磁盘
     *
     * @return true
     * @return false
     */
    bool dump(void);

    /**
     * @brief 固化到磁盘
     *
     * @param param 指定配置参数
     * @return true
     * @return false
     */
    bool dump(const param_json_t &param);

    /**
     * @brief 获取读写锁引用
     *
     * @return RwMutex&
     */
    hv::RWLock &lock() { return mtx_; }

private:
    Parameter(const std::string &path);
    ~Parameter();

    DISABLE_COPY(Parameter);

private:
    hv::RWLock mtx_;  ///< 读写锁
    std::string path_;    ///< 配置路径
    param_json_t param_;        ///< 参数
};

/**
 * @brief 获取参数值，只用该接口去获取
 * @param key 为json的key和正常使用方式相同
 */
#define GET_PARAM_ONCE(key)                                           \
    ({                                                                \
        arss::RMutexGuard lck(                                 \
            biot::Parameter::get_instance().lock());        \
        biot::Parameter::get_instance().parameter_ref() key; \
    })

/**
 * @brief 设置参数值，只用该接口去设置
 * @param key 为json的key和正常使用方式相同
 */
#define SET_PARAM_ONCE(key, value)                                            \
    ({                                                                        \
        arss::WMutexGuard lck(                                         \
            biot::Parameter::get_instance().lock());                \
        biot::Parameter::get_instance().parameter_ref() key = value; \
        biot::Parameter::get_instance().dump();                     \
    })

// TODO
#define PARAM_CONTAINS(one_key)

} // namespace biot
