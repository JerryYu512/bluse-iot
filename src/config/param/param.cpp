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
#include <time.h>
#include "hv/hfile.h"
#include "hv/json.hpp"
#include "hv/crc.h"
#include "hv/hthread.h"
#include "hv/htime.h"
#include "hv/uuid.h"
#include "config/configure.h"
#include "basic/base/proto_json.h"
#include "basic/log/biot_log.h"
#include "basic/defs/error_code.h"
#include "config/sec_param.h"
#include "param_def/param.if.h"
#include "param.h"

namespace biot {

class AppParamLockImpl {
public:
	void wrlock(const char* file, const char* func, int line) {
		BIOT_TRACE("app-param wrlock--[file:%s func:%s line:%d]\n", file, func, line);
		mtx_.wrlock();
	}
	void wrunlock(const char* file, const char* func, int line) {
		BIOT_TRACE("app-param wrunlock--[file:%s func:%s line:%d]\n", file, func, line);
		mtx_.wrunlock();
	}
	void rdlock(const char* file, const char* func, int line) {
		BIOT_TRACE("app-param rdlock--[file:%s func:%s line:%d]\n", file, func, line);
		mtx_.rdlock();
	}
	void rdunlock(const char* file, const char* func, int line) {
		BIOT_TRACE("app-param rdunlock--[file:%s func:%s line:%d]\n", file, func, line);
		mtx_.rdunlock();
	}
	void lock(const char* file, const char* func, int line) {
		BIOT_TRACE("app-param lock--[file:%s func:%s line:%d]\n", file, func, line);
		mtx_.lock();
	}
	void unlock(const char* file, const char* func, int line) {
		BIOT_TRACE("app-param unlock--[file:%s func:%s line:%d]\n", file, func, line);
		mtx_.unlock();
	}
private:
	hv::RWLock mtx_;
};

class ParamChangeRecord {
public:
	ParamChangeRecord()
		:change_cnt_(0), 
		 change_cnt_once_(0), 
		 last_change_time_(0),
		 first_change_time_(0),
		 last_write_time_(0) {}
	void inc(void) {
		if (!first_change_time_) {
			first_change_time_ = time(nullptr);
		}
		last_change_time_ = time(nullptr);
		change_cnt_++;
		change_cnt_once_++;
	}
	uint64_t changed(void) {
		return change_cnt_;
	}
	uint64_t changed_from_last(void) {
		return change_cnt_once_;
	}
	void reset_changed(void) {
		change_cnt_once_ = 0;
	}
	time_t last_time(void) {
		return last_change_time_;
	}

public:
	uint64_t change_cnt_;		// 变更次数
	uint64_t change_cnt_once_;	// 上次变更次数
	time_t last_change_time_;	// 从上次以来的变更次数
	time_t first_change_time_;
	time_t last_write_time_;	// 上次保存时间
	std::mutex mtx_;
};

extern biot_err_t reset_default_param(BiotAppParam &param);

// 全局锁
AppParamLock gBiotAppParamLock;

// 参数
static app_param_check_t g_biot_app_param_check;
static BiotAppParam g_biot_app_param;
static ParamChangeRecord g_biot_app_param_change;

static biot_err_t write_param_file(const char* path);

AppParamLock::AppParamLock() {
	impl = new AppParamLockImpl;
}

AppParamLock::~AppParamLock() {
	delete impl;
}

void AppParamLock::wrlock(const char* file, const char* func, int line) {
	impl->wrlock(file, func, line);
}

void AppParamLock::wrunlock(const char* file, const char* func, int line) {
	impl->wrunlock(file, func, line);
}

void AppParamLock::rdlock(const char* file, const char* func, int line) {
	impl->rdlock(file, func, line);
}

void AppParamLock::rdunlock(const char* file, const char* func, int line) {
	impl->rdunlock(file, func, line);
}

void AppParamLock::lock(const char* file, const char* func, int line) {
	impl->lock(file, func, line);
}

void AppParamLock::unlock(const char* file, const char* func, int line) {
	impl->unlock(file, func, line);
}

// 参数保存任务
static void* biot_app_param_dump_task(void* arg) {
	hthread_set_tname("biotParamDump");

	while (1) {
		BIOT_INFO("dump app param to file\n");
		// 5秒写一次文件
		hv_delay(5 * 1000);
		g_biot_app_param_change.mtx_.lock();
		// 检查变化
		if (g_biot_app_param_change.changed_from_last()) {
			BIOT_APP_PARAM_RLOCK;
			auto ret = write_param_file(BIOT_CONFIG_FILENAME);
			BIOT_APP_PARAM_RUNLOCK;
			if (BIOT_ECODE_OK != ret) {
				BIOT_ERROR("cycle write param failed[0x%x]: %s\n", ret, query_error_code_en(ret));
			} else {
				BIOT_TRACE("cycle write param success[total_changed=%ld, last_changed=%ld, last_time=%zu]\n",
					g_biot_app_param_change.changed(), g_biot_app_param_change.changed_from_last(), g_biot_app_param_change.last_write_time_);
				g_biot_app_param_change.last_write_time_ = time(nullptr);
				g_biot_app_param_change.reset_changed();
			}
		}
		g_biot_app_param_change.mtx_.unlock();
	}

	return nullptr;
}

static biot_err_t read_param_file(const char* path) {
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

	// 设备类型
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

	simdjson::dom::element elm;
	simdjson::dom::parser parser;
	simdjson::dom::document doc;
	// json解析
	auto err = parser.parse(p).get(elm);
	if (err != simdjson::SUCCESS) {
		BIOT_ERROR("json parse error: %s\n", simdjson::error_message(err));
		return BIOT_COMMON_ECODE_DATA_JSON_FMT_ERROR;
	}

	// json转换
	if (!json2struct(elm, param)) {
		BIOT_ERROR("json2struct error\n");
		return BIOT_COMMON_ECODE_DATA_STRUCT_TO_JSON_ERROR;
	}

	g_biot_app_param = param;
	g_biot_app_param_check = check;

	BIOT_TRACE("read param file success\n");
	return BIOT_ECODE_OK;
}

static biot_err_t write_param_file(const char* path) {
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
	g_biot_app_param_check.storage_type = APP_PARAM_FILE_STORAGE_JSON;
	g_biot_app_param_check.storage_source = APP_PARAM_FILE_STORAGE_BASELINE;
	g_biot_app_param_check.storage_version = APP_PARAM_FILE_STOREAGE_VERSION;
	g_biot_app_param_check.devtype = get_sec_param().devtype;
	datetime_t dt = datetime_now();
	datetime_fmt_iso(&dt, (char*)g_biot_app_param_check.update_time);
	memcpy(g_biot_app_param_check.product_no, get_sec_param().product_no, sizeof(g_biot_app_param_check.product_no));
	memset(g_biot_app_param_check.uuid, 0, sizeof(g_biot_app_param_check.uuid));
	uuid_generate((char*)g_biot_app_param_check.uuid);
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

	return BIOT_ECODE_OK;
}

static biot_err_t load_app_param(const char* path, const char*backup_path, const char* patch_path) {
	if (!path || !backup_path) {
		BIOT_CRITICAL("path null\n");
		return BIOT_COMMON_ECODE_MEM_INVALID;
	}

	HFile f;
	memset(&g_biot_app_param_check, 0, sizeof(g_biot_app_param_check));

	if (!read_param_file(path) && !read_param_file(backup_path)) {
		return write_param_file(path);
	}

	return BIOT_ECODE_OK;
}

biot_err_t init_app_param(void) {
	auto ret = load_app_param(BIOT_CONFIG_FILENAME, BIOT_CONFIG_BACKUP_FILENAME, BIOT_CONFIG_PATCH_FILENAME);
	if (BIOT_ECODE_OK != ret) {
		BIOT_ERROR("load app param failed[0x%x]: %s\n", ret, query_error_code_en(ret));
		BIOT_WARN("reset default parameter.\n");
		ret = reset_default_param(g_biot_app_param);
		if (BIOT_ECODE_OK != ret) {
			BIOT_ERROR("reset default parameter failed[0x%x], %s\n", ret, query_error_code_en(ret));
			return ret;
		} else {
			save_app_param(true);
		}
	}
	
	hthread_create((hthread_routine)biot_app_param_dump_task, nullptr);

	return BIOT_ECODE_OK;
}

biot_err_t save_app_param(bool now) {
	if (now) {
		return write_param_file(BIOT_CONFIG_FILENAME);
	}
	g_biot_app_param_change.mtx_.lock();
	g_biot_app_param_change.inc();
	g_biot_app_param_change.mtx_.unlock();
	return BIOT_ECODE_OK;
}

app_param_check_t& app_param_header(void) {
	return g_biot_app_param_check;
}

BiotAppParam& app_param(void) {
	return g_biot_app_param;
}
	
} // namespace biot
