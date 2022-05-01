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
 * @file proto_json.h
 * @brief 
 * @author Jerry.Yu (jerry.yu512outlook.com)
 * @version 1.0.0
 * @date 2022-05-01
 * 
 * @copyright MIT License
 * 
 */
#include <google/protobuf/util/json_util.h>

namespace biot {

static inline bool proto_to_json(const google::protobuf::Message& message, std::string& json, bool ws = true) {
    google::protobuf::util::JsonPrintOptions options;
    options.add_whitespace = ws;
    options.always_print_primitive_fields = true;
    options.preserve_proto_field_names = true;
    return google::protobuf::util::MessageToJsonString(message, &json, options).ok();
}

static inline bool json_to_proto(const std::string& json, google::protobuf::Message& message) {
    return google::protobuf::util::JsonStringToMessage(json, &message).ok();
}

}