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
 * @file ds.h
 * @brief 数据类型定义
 * @author Jerry.Yu (jerry.yu512outlook.com)
 * @version 1.0.0
 * @date 2022-04-03
 * 
 * @copyright MIT License
 * 
 */
#pragma once
#include <stdint.h>
#include <stddef.h>
#include <string>
#include <string.h>
#include <errno.h>

namespace biot {

template <typename T>
struct MaxMin {
	T max;		///< 最大
	T min;		///< 最小
	T def;		///< 默认
};

/**
 * @brief 二进制传输数据头
 * 
 */
typedef struct bin_data_header_s {
	uint32_t magic;			///< 幻数
	uint32_t res;			///< 预留用于对齐
	uint32_t checksum;		///< 校验和，长度之后开始计算
	uint32_t length;		///< 长度，该参数之后开始计算
} bin_data_header_t;

} // namespace biot
