/**
 * MIT License
 * 
 * Copyright © 2022 <Jerry.Yu>.
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software
 * and associated documentation files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the
 * 
 * The above copyright notice and this permission notice shall be included in all copies or
 * substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS";, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
 * BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 * 
 * @file param.cpp
 * @brief 
 * @author Jerry.Yu (jerry.yu512outlook.com)
 * @version 1.0.0
 * @date 2022-04-03
 * 
 * @copyright MIT License
 * 
 */
#include "hv/hfile.h"
#include "hv/json.hpp"
#include "hv/crc.h"
#include "hv/hthread.h"
#include "hv/htime.h"
#include "config/configure.h"
#include "basic/base/proto_json.h"
#include "basic/log/biot_log.h"
#include "basic/defs/error_code.h"
#include "config/sec_param.h"
#include "param_def/param.if.h"
#include "param.h"

namespace biot {

hv::RWLock gBiotAppParamLock;

// 参数
static app_param_check_t g_biot_app_param_check;
static BiotAppParam g_biot_app_param;

// 参数保存任务
static void* biot_app_param_dump_task(void* arg) {
	hthread_set_tname("biotParamDump");

	while (1) {
		BIOT_INFO("dump app param to file\n");
		hv_delay(3 * 1000);
	}

	return nullptr;
}

static int read_param_file(const char* path) {
	if (hv_exists(path)) {
		BIOT_ERROR("file: \"%s\" not exist\n", path);
		return BIOT_COMMON_ECODE_FILE_NOT_EXIST;
	}
	HFile f;
	BiotAppParam param;
	app_param_check_t check;

	// 打开文件
	auto ret = f.open(path, "r");
	if (ret) {
		BIOT_ERROR("open file error: %s\n", strerror(ret));
		return BIOT_COMMON_ECODE_FILE_OPEN_FAILED;
	}
	// 读文件头
	auto headlen = f.read(&check, sizeof(check));
	if (headlen != sizeof(check)) {
		BIOT_ERROR("param.bin header mismatch\n");
		return BIOT_SYS_ECODE_CFG_FILE_HEADER_ERROR;
	}

	// 校验
	// 幻数
	if (check.header.magic != BIOT_PARAM_FILE_MAGIC) {
		return BIOT_SYS_ECODE_CFG_FILE_HEADER_CHECK_FAILED;
	}

	// 长度
	if ((check.header.length + sizeof(bin_data_header_t)) != hv_filesize(path)
		|| (check.param_len + sizeof(app_param_check_t)) != hv_filesize(path)) {
		return BIOT_SYS_ECODE_CFG_FILE_HEADER_CHECK_FAILED;
	}

	// TODO:设备类型
	// check.devtype;
	if (check.devtype != get_sec_param().devtype) {
		BIOT_ERROR("param type: %d, sec type: %d\n", check.devtype, get_sec_param().devtype);
		return BIOT_SYS_ECODE_CFG_FILE_HEADER_CHECK_FAILED;
	}

	// 内存分配
	simdjson::padded_string p(check.param_len);
	// 读参数
	auto bodylen = f.read(p.data(), check.param_len);
	if (bodylen != check.param_len) {
		return BIOT_COMMON_ECODE_FILE_READ_FAILED;
	}

	simdjson::ondemand::parser parser;
	simdjson::dom::element elm;
	// TODO:错误处理
	parser.iterate(p).get(elm);
	if (!json2struct(elm, param)) {
		return BIOT_COMMON_ECODE_DATA_STRUCT_TO_JSON_ERROR;
	}

	g_biot_app_param = param;
	g_biot_app_param_check = check;

	return BIOT_SYS_ECODE_OK;
}

static int write_param_file(const char* path) {
	HFile f;

	auto ret = f.open(path, "w+");
	if (ret) {
		BIOT_CRITICAL("create file \"%s\" error: %s\n", path, strerror(errno));
		return BIOT_COMMON_ECODE_FILE_OPEN_FAILED;
	}
	// json转换
	nlohmann::json js;
	if (!struct2json(g_biot_app_param, js)) {
		BIOT_CRITICAL("trans struct to json error\n");
		return BIOT_COMMON_ECODE_DATA_STRUCT_TO_JSON_ERROR;
	}

	auto jstr = js.dump();
	g_biot_app_param_check.header.magic = BIOT_PARAM_FILE_MAGIC;
	g_biot_app_param_check.header.length = sizeof(app_param_check_t) - sizeof(bin_data_header_t) + jstr.length();
	g_biot_app_param_check.param_len = jstr.length();
	// TODO:其他信息
	// 计算校验码
	uint32_t crc = 0;
	crc = crc32(crc, (const uint8_t*)&g_biot_app_param_check.storage_type, sizeof(app_param_check_t) - sizeof(bin_data_header_t));
	crc = crc32(crc, (const uint8_t*)jstr.data(), jstr.length());
	g_biot_app_param_check.header.checksum = crc;

	if (sizeof(app_param_check_t) != f.write(&g_biot_app_param_check, sizeof(app_param_check_t))) {
		return BIOT_COMMON_ECODE_FILE_WRITE_FAILED;
	}
	if (jstr.length() != f.write(jstr.data(), jstr.length())) {
		return BIOT_COMMON_ECODE_FILE_WRITE_FAILED;
	}

	return BIOT_SYS_ECODE_OK;
}

static int load_app_param(const char* path, const char*backup_path, const char* patch_path) {
	if (!path || !backup_path) {
		BIOT_CRITICAL("path null\n");
		return BIOT_COMMON_ECODE_MEM_INVALID;
	}

	HFile f;
	memset(&g_biot_app_param_check, 0, sizeof(g_biot_app_param_check));

	if (!read_param_file(path) && !read_param_file(backup_path)) {
		return write_param_file(path);
	}

	return BIOT_SYS_ECODE_OK;
}

int init_app_param(void) {
	auto ret = load_app_param(BIOT_CONFIG_FILENAME, BIOT_CONFIG_BACKUP_FILENAME, BIOT_CONFIG_PATCH_FILENAME);
	if (BIOT_SYS_ECODE_OK == ret) {
		hthread_create((hthread_routine)biot_app_param_dump_task, nullptr);
	}

	return ret;
}

int save_app_param(bool now) {
	if (now) {
		return write_param_file(BIOT_CONFIG_FILENAME);
	}
	return 0;
}

app_param_check_t& app_param_header(void) {
	return g_biot_app_param_check;
}

BiotAppParam& app_param(void) {
	return g_biot_app_param;
}
	
} // namespace biot
