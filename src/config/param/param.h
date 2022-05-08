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
#include "param_def/param.pm.h"

namespace biot {

// 写锁
#define BIOT_APP_PARAM_WLOCK
// 读锁
#define BIOT_APP_PARAM_RLOCK
// 解锁
#define BIOT_APP_PARAM_UNLOCK
	
/**
 * @brief 加载参数
 * 
 * @param path 参数路径
 * @param backup_path 参数备份路径
 * @param patch_path 补丁路径
 * @return int 结果
 */
int load_app_param(const char* path, const char*backup_path, const char* patch_path);

/**
 * @brief 保存参数
 * 
 * @param now 立即写flash
 * @return int 
 */
int save_app_param(bool now = false);

/**
 * @brief 获取参数引用
 * 
 * @return BiotAppParam& 
 */
BiotAppParam& app_param(void);
	
} // namespace biot
