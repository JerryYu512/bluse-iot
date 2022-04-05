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
 * @file result.h
 * @brief 
 * @author Jerry.Yu (jerry.yu512@outlook.com)
 * @version 1.0.0
 * @date 2022-04-05
 * 
 * @copyright MIT License
 * 
 */
#pragma once
#include <stdint.h>
#include <string>
#include <string.h>
#include "brsdk/err/err.hpp"

namespace biot {

#define BIOT_ID_CODE 1ull

#define BIOT_ERR_PRE BEC_ADD_ID_CODE(BIOT_ID_CODE, BEC_ADD_CLASS_CODE(BEC_COMMON_APPLICATION, BEC_ADD_IDENTIFICATION_CODE(BEC_IDENTI_APPLICATION, 0)))

typedef brsdk::berror_t biot_err_t;

/**
 * @brief 操作结果
 * 
 */
class Result {
public:
	std::string msg;	///< 短语

	// 系统错误码
	virtual int sys_errno(void) {
		return errno;
	}

	// 应用错误码
	virtual biot_err_t app_errno(void) {
		return brsdk::berrno;
	}

	// 系统错误短语
	virtual std::string strerr(void) {
		return ::strerror(errno);
	}

	// 错误
	virtual std::string what(void) {
		return msg;
	}

	// 设置错误短语
	virtual void whatsup(const char* msg) {
		this->msg = msg;
	}

	virtual void whatsup(const std::string& msg) {
		this->msg = msg;
	}

	virtual void sys_error(biot_err_t domain_id, biot_err_t code);
	virtual void subsys_error(biot_err_t domain_id, biot_err_t code);
	virtual void protocol_error(biot_err_t domain_id, biot_err_t code);
	virtual void auth_error(biot_err_t domain_id, biot_err_t code);
	virtual void net_error(biot_err_t domain_id, biot_err_t code);
	virtual void device_error(biot_err_t domain_id, biot_err_t code);
	virtual void param_error(biot_err_t domain_id, biot_err_t code);
	virtual void service_error(biot_err_t domain_id, biot_err_t code);
	virtual void source_error(biot_err_t domain_id, biot_err_t code);
	virtual void other_error(biot_err_t domain_id, biot_err_t code);
};

} // namespace biot
