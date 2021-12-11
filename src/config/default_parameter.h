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
 * @file default_parameter.h
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
#include <vector>
#include <stdint.h>

namespace ars {

namespace iot {

#define PARAMETER_TYPE(XX) \
XX(bool, "bool") \
XX(int8, "int8") \
XX(uint8, "unsigned int8") \
XX(int16, "int16") \
XX(uint16, "unsigned int16") \
XX(int, "int") \
XX(uint, "unsigned int") \
XX(int64, "int64") \
XX(uint64, "unsigned int64") \
XX(float, "float") \
XX(double, "double") \
XX(string, "string") \
XX(array, "array") \
XX(object, "object")

#define PARAMETER_PERMISSION(XX) \
XX(read, "r") \
XX(write, "w") \
XX(read_write, "rw")

/**
 * @brief 参数类型
 * 
 */
typedef enum {
#define XX(type, desc) param_t_##type,
	PARAMETER_TYPE(XX)
#undef XX
} parameter_type_e;

/**
 * @brief 参数读写权限
 * 
 */
typedef enum {
#define XX(p, desc) param_p_##p,
	PARAMETER_PERMISSION(XX)
#undef XX
} parameter_permission_e;

///< 参数配置
typedef struct parameter_config_s parameter_config_t;

/**
 * @brief 参数配置
 * 
 */
struct parameter_config_s {
	std::string name;								///< 参数名称
	std::string desc;								///< 参数描述
	parameter_type_e type;							///< 参数类型
	std::string range;								///< 参数范围
	parameter_permission_e permission;				///< 参数读写权限
	std::string value;								///< 参数值，基本类型时填写其字符串，数组、对象时填写json格式字符串
	parameter_type_e sub_type;						///< 子类型，仅在参数类型为数组时有效
	std::vector<parameter_config_t*> sub_value;		///< 子参数列表
};

/**
 * @brief Get the paramter type object
 * 
 * @param type 类型
 * @return const char* 类型字符串
 */
const char* get_paramter_type(parameter_type_e type);

/**
 * @brief Get the paramter permission object
 * 
 * @param permission 权限
 * @return const char* 权限字符串
 */
const char* get_paramter_permission(parameter_permission_e permission);

/**
 * @brief Get the default parameter object
 * 
 * @return const char* 默认参数字符串
 */
std::string get_default_parameter(void);

} // namespace iot

} // namespace ars
