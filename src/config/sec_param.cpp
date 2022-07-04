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
 * @file sec_param.cpp
 * @brief 
 * @author Jerry.Yu (jerry.yu512outlook.com)
 * @version 1.0.0
 * @date 2022-05-16
 * 
 * @copyright MIT License
 * 
 */
#include "hv/hfile.h"
#include "hv/crc.h"
#include "configure.h"
#include "sec_param.h"

namespace biot {

static sec_param_t sec_param;
	
int read_sec_param(void) {
#if 0
	HFile f;
	memset(&sec_param, 0, sizeof(sec_param));

	f.open(BIOT_SEC_PARAM_FILENAME, "r");
#else
	memset(&sec_param, 0, sizeof(sec_param));
	// TODO:

	sec_param.header.magic = BIOT_SEC_INFO_MAGIC;
	sec_param.header.length = sizeof(sec_param_t) - sizeof(bin_data_header_t);
	sec_param.header.checksum = crc32(0, (uint8_t*)&sec_param.devtype, sec_param.header.length);
#endif

	return 0;
}

const sec_param_t& get_sec_param(void) {
	return sec_param;
}

} // namespace biot
