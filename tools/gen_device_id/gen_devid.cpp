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
 * @file gen_devid.cpp
 * @brief 
 * @author Jerry.Yu (jerry.yu512outlook.com)
 * @version 1.0.0
 * @date 2022-07-24
 * 
 * @copyright MIT License
 * 
 */
#include "src/config/sec_param.h"
#include "argparse.hpp"

using namespace argparse;
using namespace biot;

int main(void) {
	ArgumentParser parser("gen_devid", "gen device id");
	// parser.add_argument()
    //   .names({"-v", "--verbose"})
    //   .description("verbose level")
    //   .required(true);
	parser.add_argument("-o", "--organize", "组织", true);
	parser.add_argument("-l", "--line", "产品线", true);
	parser.add_argument("-c", "--class", "产品大类", true);
	parser.add_argument("-p", "--platform", "平台", true);
	parser.add_argument("-m", "--major", "主类型", true);
	parser.add_argument("-s", "--minor", "次类型", true);
	parser.add_argument("--language", "语言", true);
	parser.add_argument("-b", "--base", "基线", true);
	// parser.add_argument("-d", "--date", "生产日期", true);
	// parser.add_argument("-u", "--update", "更新日期", true);
	// parser.add_argument("-n", "--no", "序列号", true);
	// parser.add_argument("--mac", "mac地址", true);
	parser.add_argument("-n", "--name", "产品型号", true);
	parser.enable_help();
	auto err = parser.parse(argc, argv);
	if (err) {
		std::cout << err << std::endl;
		return -1;
	}
	return 0;
}