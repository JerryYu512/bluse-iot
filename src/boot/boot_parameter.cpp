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
 * @file boot_parameter.cpp
 * @brief 
 * @author wotsen (astralrovers@outlook.com)
 * @version 1.0.0
 * @date 2021-08-15
 * 
 * @copyright MIT License
 * 
 */
#include "boot.h"
#include "arss/fs/file.hpp"
#include "arss/fs/file_util.hpp"
#include "arss/json/json.hpp"
#include "arss/str/pystring.hpp"
#include "arss/time/timestamp.hpp"
#include "config/default_parameter.h"
#include "config/args_dec.h"
#include "config/configure.h"
#include "log/ars_iot_log.h"
#include "core/version.h"
#include "core/parameter.h"

namespace ars {

namespace iot {

using namespace nlohmann;

int boot_parameter(void) {
	// 获取默认参数
	json def_param = json::parse(get_default_parameter());
	std::string param_path = pystring::os::path::join(FLG_abs_rt_path, IOT_CONFIG_FILENAME);
	std::string param_patch_path = pystring::os::path::join(FLG_abs_rt_path, IOT_CONFIG_PATCH_FILENAME);
	arss::fs::File fd;

	// 历史参数
	if (arss::fs::fs_exists(param_path.c_str()) && arss::fs::fs_size(param_path.c_str()) > 0) {
		iot_boot_printi("merge old param\n");
		json param;
		std::string str;
		if (fd.open(param_path.c_str(), "r+") < 0) {
			iot_boot_printe("open param file : %s error\n", param_path.c_str());
			return BOOT_REBOOT;
		}
		fd.readall(str);
		if (str.empty()) {
			iot_boot_printi("param file is empty\n");
		} else {
			param = json::parse(str);
			// 参数合并
			def_param.merge_patch(param);
		}
		fd.close();
	}

	// 补丁文件
	if (arss::fs::fs_exists(param_patch_path.c_str()) && arss::fs::fs_size(param_patch_path.c_str()) > 0) {
		iot_boot_printi("patch param\n");
		std::string str;
		json param;
		if (fd.open(param_patch_path.c_str(), "r+") < 0) {
			iot_boot_printe("open param file : %s error\n", param_patch_path.c_str());
			return BOOT_REBOOT;
		}
		fd.readall(str);
		if (str.empty()) {
			iot_boot_printi("param file is empty\n");
		} else {
			param = json::parse(str);
			// 参数补丁
			def_param.patch(param);
		}
		fd.close();
		arss::fs::fs_remove(param_patch_path.c_str());
	}

	iot_boot_printi("update param version and value\n");
	// 更新时间和版本
	def_param["param header"]["version"]["value"] = "v" + app_version() + " " + app_build_version();
	def_param["param header"]["save date"]["value"] = arss::Timestamp::now().toFormattedString();

	iot_boot_printi("save new param : %s\n", param_path.c_str());
	// 保存最新的参数
	if (fd.open(param_path.c_str(), "w+") < 0) {
		iot_boot_printe("open param file : %s error\n", param_path.c_str());
		return BOOT_REBOOT;
	}

	iot_boot_printi("dump param\n");
#ifdef DEBUG
	std::string new_param_str = def_param.dump(4);
#else
	std::string new_param_str = def_param.dump();
#endif
	iot_boot_printi("param:\n%s\n", new_param_str.c_str());
	fd.write(new_param_str.c_str(), new_param_str.length());
	fd.sync();
	fd.close();

	Parameter::get_instance(param_path);

	return BOOT_OK;
}

void boot_un_parameter(void) {

}

} // namespace iot
} // namespace ars
