/**
 * MIT License
 * 
 * Copyright © 2021 <wotsen>.
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software
 * and associated documentation files (the “Software”), to deal in the Software without
 * restriction, including without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the
 * 
 * The above copyright notice and this permission notice shall be included in all copies or
 * substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
 * BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 * 
 * @file parameter.cpp
 * @brief 
 * @author wotsen (astralrovers@outlook.com)
 * @version 1.0.0
 * @date 2021-08-15
 * 
 * @copyright MIT License
 * 
 */
#include "parameter.h"
#include <fstream>
#include <iomanip>
#include <iostream>
#include <stdexcept>

namespace biot {

Parameter::Parameter(const std::string &path) : path_(path) {
    try {
        std::ifstream f(path);
        f >> param_;
    } catch (const param_json_t::parse_error &e) {
        throw std::invalid_argument(e.what());
    }
}

Parameter::~Parameter() {
    dump();
}

void Parameter::init(const std::string &path) {
    Parameter::get_instance(path);
}

Parameter &Parameter::get_instance(const std::string &path) {
    static Parameter param(path);
    return param;
}

param_json_t &Parameter::parameter_ref(void) { return param_; }

bool Parameter::dump(void) {
    std::ofstream f(path_);
    f << std::setw(4) << param_ << std::endl;
    f.flush();

    return true;
}

bool Parameter::dump(const param_json_t &param) {
    param_ = param;
    return dump();
}

} // namespace biot
