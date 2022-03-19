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
 * @file default_parameter.cpp
 * @brief 
 * @author wotsen (astralrovers@outlook.com)
 * @version 1.0.0
 * @date 2021-08-15
 * 
 * @copyright MIT License
 * 
 */
#include "default_parameter.h"
#include "brsdk/json/json.hpp"
#include "brsdk/str/fmt.hpp"
#include "log/biot_log.h"

namespace biot {

using namespace nlohmann;

static void generate_def_json_array(parameter_config_t *cfg, json &node);
static void generate_def_json_obj(parameter_config_t *cfg, json &node);

/////////////////////////////////////////////////////
/// 能力级
/////////////////////////////////////////////////////

extern parameter_config_t def_capability;

////////////////////////////////////////////////////
/// 设备信息
////////////////////////////////////////////////////

extern parameter_config_t def_device_info_param;

////////////////////////////////////////////////////
/// 模块
////////////////////////////////////////////////////

extern parameter_config_t def_module_param;

////////////////////////////////////////////////////

///< 类型映射
const char* types[] = {
#define XX(type, str) str,
	PARAMETER_TYPE(XX)
#undef XX
};

///< 权限映射
const char* permissions[] = {
#define XX(p, desc) desc,
	PARAMETER_PERMISSION(XX)
#undef XX
};

parameter_config_t def_param_header = {
	"param header",
	"参数头",
	param_t_object,
	"NA",
	param_p_read_write,
	R"(
	{
		"version": {
			"desc": "版本号",
			"type": "string",
			"range": "NA",
			"permission": "r",
			"value": "v1.0.0 build 20210101"
		},
		"save date": {
			"desc": "保存日期",
			"type": "string",
			"range": "NA",
			"permission": "r",
			"value": "20210101 00:00:00"
		}
	}
	)",
	param_t_object,
	{
	}
};

///< 默认配置
static std::vector<parameter_config_t*> def_param = {
	&def_param_header,
	&def_capability,
	&def_device_info_param,
	&def_module_param,
};

const char* get_paramter_type(parameter_type_e type) {
	return types[type];
}

const char* get_paramter_permission(parameter_permission_e permission) {
	return permissions[permission];
}

static void generate_def_json_obj(parameter_config_t *cfg, json &node) {
	// 子参数列表为空
	if (cfg->sub_value.empty()) {
		if (cfg->value.empty()) {
			// 值为空时，给个空对象
			node["value"] = json::object();
		} else {
			// 解析，如果不是对象类型，则报错
			try {
				node["value"] = json::parse(cfg->value);
				if (!node["value"].is_object()) {
					throw std::invalid_argument("not object: " + cfg->value);
				}
			} catch (const json::parse_error& e) {
				biot_boot_printe("parser error(%s), name=\"%s\", value=\n%s\n", e.what(), cfg->name.c_str(), cfg->value.c_str());
				throw std::invalid_argument(e.what());
			}
		}
		return ;
	}

	if (!cfg->value.empty()) {
		try {
			node["value"] = json::parse(cfg->value);
		} catch (const json::parse_error& e) {
			biot_boot_printe("parser error(%s), name=\"%s\", value=\n%s\n", e.what(), cfg->name.c_str(), cfg->value.c_str());
			throw std::invalid_argument(e.what());
		}
	} else {
		node["value"] = json::object();
	}

	// 检查是不是对象
	if (!node["value"].is_object()) {
		throw std::invalid_argument("not object: " + cfg->value);
	}

	for (auto & item : cfg->sub_value) {
		node["value"][item->name]["desc"] = item->desc;
		node["value"][item->name]["type"] = get_paramter_type(item->type);
		node["value"][item->name]["range"] = item->range;
		node["value"][item->name]["permission"] = get_paramter_permission(item->permission);
		node["value"][item->name]["sub type"] = get_paramter_type(item->sub_type);
		if (param_t_bool == item->type) {
			node["value"][item->name]["value"] = brsdk::str::to_bool(item->value);
		} else if (param_t_int8 == item->type) {
			node["value"][item->name]["value"] = brsdk::str::to_int32(item->value);
		} else if (param_t_uint8 == item->type) {
			node["value"][item->name]["value"] = brsdk::str::to_uint32(item->value);
		} else if (param_t_int16 == item->type) {
			node["value"][item->name]["value"] = brsdk::str::to_int32(item->value);
		} else if (param_t_uint16 == item->type) {
			node["value"][item->name]["value"] = brsdk::str::to_uint32(item->value);
		} else if (param_t_int == item->type) {
			node["value"][item->name]["value"] = brsdk::str::to_int32(item->value);
		} else if (param_t_uint == item->type) {
			node["value"][item->name]["value"] = brsdk::str::to_uint32(item->value);
		} else if (param_t_int64 == item->type) {
			node["value"][item->name]["value"] = brsdk::str::to_int64(item->value);
		} else if (param_t_uint64 == item->type) {
			node["value"][item->name]["value"] = brsdk::str::to_uint64(item->value);
		} else if (param_t_float == item->type) {
			node["value"][item->name]["value"] = brsdk::str::to_double(item->value);
		} else if (param_t_double == item->type) {
			node["value"][item->name]["value"] = brsdk::str::to_double(item->value);
		} else if (param_t_string == item->type) {
			node["value"][item->name]["value"] = item->value;
		} else if (param_t_array == item->type) {
			generate_def_json_array(item, node["value"][item->name]);
		} else {
			generate_def_json_obj(item, node["value"][item->name]);
		}
	}
}

static void generate_def_json_array(parameter_config_t *cfg, json &node) {
	// 空的就直接解析
	if (cfg->sub_value.empty()) {
		if (cfg->value.empty()) {
			node["value"] = json::array();
		} else {
			try {
				node["value"] = json::parse(cfg->value);
				if (!node["value"].is_array()) {
					throw std::invalid_argument("not array: " + cfg->value);
				}
			} catch (const json::parse_error& e) {
				biot_boot_printe("parser error(%s), name=\"%s\", value=\n%s\n", e.what(), cfg->name.c_str(), cfg->value.c_str());
				throw std::invalid_argument(e.what());
			}
		}
		return ;
	}

	if (!cfg->value.empty()) {
		try {
			node["value"] = json::parse(cfg->value);
		} catch (const json::parse_error& e) {
			biot_boot_printe("parser error(%s), name=\"%s\", value=\n%s\n", e.what(), cfg->name.c_str(), cfg->value.c_str());
			throw std::invalid_argument(e.what());
		}
	} else {
		node["value"] = json::array();
	}

	// 检查是不是数组
	if (!node["value"].is_array()) {
		throw std::invalid_argument("not array: " + cfg->value);
	}

	for (auto & item : cfg->sub_value) {
		json j;

		if (param_t_bool == cfg->sub_type) {
			node["value"].push_back(brsdk::str::to_bool(item->value));
		} else if (param_t_int8 == cfg->sub_type) {
			node["value"].push_back(brsdk::str::to_int32(item->value));
		} else if (param_t_uint8 == cfg->sub_type) {
			node["value"].push_back(brsdk::str::to_uint32(item->value));
		} else if (param_t_int16 == cfg->sub_type) {
			node["value"].push_back(brsdk::str::to_int32(item->value));
		} else if (param_t_uint16 == cfg->sub_type) {
			node["value"].push_back(brsdk::str::to_uint32(item->value));
		} else if (param_t_int == cfg->sub_type) {
			node["value"].push_back(brsdk::str::to_int32(item->value));
		} else if (param_t_uint == cfg->sub_type) {
			node["value"].push_back(brsdk::str::to_uint32(item->value));
		} else if (param_t_int64 == cfg->sub_type) {
			node["value"].push_back(brsdk::str::to_int64(item->value));
		} else if (param_t_uint64 == cfg->sub_type) {
			node["value"].push_back(brsdk::str::to_uint64(item->value));
		} else if (param_t_float == cfg->sub_type) {
			node["value"].push_back(brsdk::str::to_double(item->value));
		} else if (param_t_double == cfg->sub_type) {
			node["value"].push_back(brsdk::str::to_double(item->value));
		} else if (param_t_string == cfg->sub_type) {
			node["value"].push_back(item->value);
		} else if (param_t_array == cfg->sub_type) {
			generate_def_json_array(item, j);
			node["value"].push_back(j["value"]);
		} else {
			j[item->name]["desc"] = item->desc;
			j[item->name]["type"] = get_paramter_type(item->type);
			j[item->name]["range"] = item->range;
			j[item->name]["permission"] = get_paramter_permission(item->permission);
			if (param_t_bool == item->type) {
				j[item->name]["value"] = brsdk::str::to_bool(item->value);
			} else if (param_t_int8 == item->type) {
				j[item->name]["value"] = brsdk::str::to_int32(item->value);
			} else if (param_t_uint8 == item->type) {
				j[item->name]["value"] = brsdk::str::to_uint32(item->value);
			} else if (param_t_int16 == item->type) {
				j[item->name]["value"] = brsdk::str::to_int32(item->value);
			} else if (param_t_uint16 == item->type) {
				j[item->name]["value"] = brsdk::str::to_uint32(item->value);
			} else if (param_t_int == item->type) {
				j[item->name]["value"] = brsdk::str::to_int32(item->value);
			} else if (param_t_uint == item->type) {
				j[item->name]["value"] = brsdk::str::to_uint32(item->value);
			} else if (param_t_int64 == item->type) {
				j[item->name]["value"] = brsdk::str::to_int64(item->value);
			} else if (param_t_uint64 == item->type) {
				j[item->name]["value"] = brsdk::str::to_uint64(item->value);
			} else if (param_t_float == item->type) {
				j[item->name]["value"] = brsdk::str::to_double(item->value);
			} else if (param_t_double == item->type) {
				j[item->name]["value"] = brsdk::str::to_double(item->value);
			} else if (param_t_string == item->type) {
				j[item->name]["value"] = item->value;
			} else if (param_t_array == item->type) {
				generate_def_json_array(item, j[item->name]);
			} else {
				generate_def_json_obj(item, j[item->name]);
			}
			node["value"].push_back(j);
		}
	}
}

std::string get_default_parameter(void) {
	json root;

	for (auto & item : def_param) {
		root[item->name]["desc"] = item->desc;
		root[item->name]["type"] = get_paramter_type(item->type);
		root[item->name]["range"] = item->range;
		root[item->name]["permission"] = get_paramter_permission(item->permission);
		root[item->name]["sub type"] = get_paramter_type(item->sub_type);
		if (param_t_bool == item->type) {
			root[item->name]["value"] = brsdk::str::to_bool(item->value);
		} else if (param_t_int8 == item->type) {
			root[item->name]["value"] = brsdk::str::to_int32(item->value);
		} else if (param_t_uint8 == item->type) {
			root[item->name]["value"] = brsdk::str::to_uint32(item->value);
		} else if (param_t_int16 == item->type) {
			root[item->name]["value"] = brsdk::str::to_int32(item->value);
		} else if (param_t_uint16 == item->type) {
			root[item->name]["value"] = brsdk::str::to_uint32(item->value);
		} else if (param_t_int == item->type) {
			root[item->name]["value"] = brsdk::str::to_int32(item->value);
		} else if (param_t_uint == item->type) {
			root[item->name]["value"] = brsdk::str::to_uint32(item->value);
		} else if (param_t_int64 == item->type) {
			root[item->name]["value"] = brsdk::str::to_int64(item->value);
		} else if (param_t_uint64 == item->type) {
			root[item->name]["value"] = brsdk::str::to_uint64(item->value);
		} else if (param_t_float == item->type) {
			root[item->name]["value"] = brsdk::str::to_double(item->value);
		} else if (param_t_double == item->type) {
			root[item->name]["value"] = brsdk::str::to_double(item->value);
		} else if (param_t_string == item->type) {
			root[item->name]["value"] = item->value;
		} else if (param_t_array == item->type) {
			generate_def_json_array(item, root[item->name]);
		} else {
			generate_def_json_obj(item, root[item->name]);
		}
	}

	return root.dump();
}

} // namespace biot
