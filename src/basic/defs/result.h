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
#include <string>
#include <string.h>
#include "error_code.h"

namespace biot {

#define BIOT_ERR_PRE BEC_ADD_ID_CODE(BIOT_ID_CODE, BEC_ADD_CLASS_CODE(BEC_COMMON_APPLICATION, BEC_ADD_IDENTIFICATION_CODE(BEC_IDENTI_APPLICATION, 0)))

/**
 * @brief 操作结果
 * 
 */
class Result {
public:
	static __thread biot_err_t berrno;	///< 错误码
	static __thread char msg[256];		///< 短语

	void result(uint64_t code, const std::string& msg, bool d = false) {
		berrno = code;
		memset(this->msg, 0, sizeof(this->msg));
		memcpy(this->msg, msg.data(), msg.length());
	}
	void result(uint64_t code, bool d = false) {
		berrno = code;
		memset(this->msg, 0, sizeof(this->msg));
	}

	// 系统错误码
	int sys_errno(void) {
		return errno;
	}

	// 应用错误码
	biot_err_t app_errno(void) {
		return berrno;
	}

	// 系统错误短语
	virtual std::string strerr(void) {
		return ::strerror(errno);
	}

	// 错误
	std::string what(void) {
		return msg;
	}
};

extern __thread Result bresult;

} // namespace biot
