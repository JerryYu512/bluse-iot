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
 * @file biot_log_map.h
 * @brief 
 * @author Jerry.Yu (jerry.yu512outlook.com)
 * @version 1.0.0
 * @date 2022-03-19
 * 
 * @copyright MIT License
 * 
 */
#pragma once

namespace biot {

/**
 * @brief 日志模块索引地址
 * 
 */
#define BIOT_LOG_INDEX_MAP(XX) \
XX(LOG_DEFAULT, "biot", LOG_LEVEL_DEF, LOG_METHOD_DEF) \
XX(LOG_API, "BiotApi", LOG_LEVEL_DEF, LOG_METHOD_DEF) \
XX(LOG_DB, "DB", LOG_LEVEL_DEF, LOG_METHOD_DEF) \
XX(LOG_PARAM, "PARAM", LOG_LEVEL_DEF, LOG_METHOD_DEF) \
XX(LOG_HWIOT, "HWIot", LOG_LEVEL_DEF, LOG_METHOD_DEF)

/**
 * @brief 日志索引
 * 
 */
enum : int {
#define XX(idx, name, level, method) BIOT_##idx,
	BIOT_LOG_INDEX_MAP(XX)
#undef XX
	BIOT_LOG_INDEX_MAX
};

} // namespace biot
