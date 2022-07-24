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
 * @file error_code.cpp
 * @brief 
 * @author Jerry.Yu (jerry.yu512outlook.com)
 * @version 1.0.0
 * @date 2022-07-24
 * 
 * @copyright MIT License
 * 
 */
#include <map>
#include <iostream>
#include <iomanip>
#include "basic/if/tabulate.hpp"
#include "error_code.h"

namespace biot {

struct ErrorStr {
	const char* en;
	const char* zh;
};

static std::map<BiotErrorCode, ErrorStr> error_code_map = {
#define BIOT_ERROR_CODE_MAP_TO_RECORD(expr, value, str, desc) {value, {str, desc}},
	BIOT_ERROR_CODE_MAP(BIOT_ERROR_CODE_MAP_TO_RECORD)
#undef BIOT_ERROR_CODE_MAP_TO_RECORD
};

const char* query_error_code_zh(BiotErrorCode no) {
	auto result = error_code_map.find(no);
	if (result != error_code_map.end()) {
		return result->second.zh;
	}

	return nullptr;
}

const char* query_error_code_en(BiotErrorCode no) {
	auto result = error_code_map.find(no);
	if (result != error_code_map.end()) {
		return result->second.en;
	}

	return nullptr;
}

void show_error_code(void) {
	tabulate::Table show;
	show.add_row({"code", "en", "zh"});
	for (auto &i : error_code_map) {
		show.add_row({std::to_string(i.first), i.second.en, i.second.zh});
		// std::cout << std::hex << i.first << ": " << i.second.en << " -- " << i.second.zh << std::endl;
	}

	for (size_t i = 0; i < 3; ++i) {
    show[0][i]
        .format()
        .font_color(tabulate::Color::yellow)
        .font_style({tabulate::FontStyle::bold});
  }

	std::cout << show << std::endl;
}

}
