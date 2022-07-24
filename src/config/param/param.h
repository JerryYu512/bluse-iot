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
 * @file param.h
 * @brief 
 * @author Jerry.Yu (jerry.yu512outlook.com)
 * @version 1.0.0
 * @date 2022-05-01
 * 
 * @copyright MIT License
 * 
 */
#pragma once
#include "hv/hmutex.h"
#include "param_check.h"
#include "param_def/param.pm.h"
#include "basic/defs/error_code.h"

namespace biot {

class AppParamLockImpl;
class AppParamLock {
public:
	AppParamLock();
	~AppParamLock();
	void wrlock(const char* file, const char* func, int line);
	void wrunlock(const char* file, const char* func, int line);
	void rdlock(const char* file, const char* func, int line);
	void rdunlock(const char* file, const char* func, int line);
	void lock(const char* file, const char* func, int line);
	void unlock(const char* file, const char* func, int line);
private:
	AppParamLockImpl *impl;
};

extern AppParamLock gBiotAppParamLock;

// 写锁
#define BIOT_APP_PARAM_WLOCK gBiotAppParamLock.wrlock(__FILE__, __func__, __LINE__)
#define BIOT_APP_PARAM_WUNLOCK gBiotAppParamLock.wrunlock(__FILE__, __func__, __LINE__)
// 读锁
#define BIOT_APP_PARAM_RLOCK gBiotAppParamLock.rdlock(__FILE__, __func__, __LINE__)
#define BIOT_APP_PARAM_RUNLOCK gBiotAppParamLock.rdunlock(__FILE__, __func__, __LINE__)

// 一般锁
#define BIOT_APP_PARAM_LOCK gBiotAppParamLock.lock(__FILE__, __func__, __LINE__)
#define BIOT_APP_PARAM_UNLOCK gBiotAppParamLock.unlock(__FILE__, __func__, __LINE__)
	
/**
 * @brief 参数初始化
 * 
 * @return int 
 */
biot_err_t init_app_param(void);

/**
 * @brief 保存参数
 * 
 * @param now 立即写flash
 * @return int 
 */
biot_err_t save_app_param(bool now = false);

/**
 * @brief 
 * 
 * @return app_param_check_t& 
 */
app_param_check_t& app_param_header(void);

/**
 * @brief 获取参数引用
 * 
 * @return BiotAppParam& 
 */
BiotAppParam& app_param(void);
	
} // namespace biot
