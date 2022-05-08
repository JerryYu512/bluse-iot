from typing import List, Dict, Set, Type
from string import Template
import argparse
import json
import re
import os

parser = argparse.ArgumentParser(prog="gen_protobuf_to_cpp", description="trans protobuf json to cxx file",
                                 usage="gen_protobuf_to_cpp [jsonfile_path] [out_path]")
parser.add_argument("--path", type=str, help="json file path")
parser.add_argument("--out", type=str, help="cxx file out path")
args = parser.parse_args()

int8_t = "int8_t"
uint8_t = "uint8_t"
int16_t = "int16_t"
uint16_t = "uint16_t"
int32_t = "int32_t"
uint32_t = "uint32_t"
int64_t = "int64_t"
uint64_t = "uint64_t"
vector = "vector"
string = "string"

enum_if_template = Template("""
#ifndef __ENUM_IF_DECL
#define __ENUM_IF_DECL

#include <stdint.h>
#include <string>
#include <map>

${head}

template <typename T>
const char* get_enum_str(T e) {
    return "";
}

template <typename T>
const char* get_enum_as_str(T e) {
    return "";
}

template <typename T>
T get_enum_value(const char* str) {
    return T();
}

template <typename T>
bool in_enum_range(T e) {
    return false;
}

${end}
#endif // __ENUM_IF_DECL
"""
)

enum_if_decl = Template(
"""
template <> const char* get_enum_str<${name}>(${name} e);
template <> const char* get_enum_as_str<${name}>(${name} e);
template <> ${name} get_enum_value<${name}>(const char* str);
template <> bool in_enum_range<${name}>(${name} e);

"""
)

struct_if_template = Template("""

#ifndef __STRUCT_IF_DECL
#define __STRUCT_IF_DECL

#include "simdjson.h"
#include "hv/json.hpp"

${head}

template <typename T>
bool json2struct(simdjson::dom::element &js, T &st) {
    return false;
}

template <typename T>
bool struct2json(const T &st, nlohmann::json &js) {
    return false;
}
${end}

#endif // __STRUCT_IF_DECL
""")

convert_nor_tp = Template("""\t{ js["${key}"] = st.${key}; }""")

convert_object_tp = Template("""\t{ nlohmann::json node; struct2json(st.${key}, node); js["${key}"] = node; }""")

convert_list_nor_tp = Template("""\t{ for (auto &value: st.${key}) { js["${key}"].push_back(value); } }""")

convert_list_object_tp = Template("""\t{ for (auto &value: st.${key}) { nlohmann::json node; struct2json(value, node); js["${key}"].push_back(node); } }""")

get_bool_value_tp = Template("""\t{
\t\tbool val = false;
\t\tif (simdjson::SUCCESS != js["${key}"].get(val) || !js["${key}"].is_bool()) {
\t\t\tif (${required}) { std::cerr << "not find [${key}]" << std::endl; }
\t\t\ttst.${key} = ${default_value};
\t\t} else { tst.${key} = val; }
\t}
""")

get_int_value_tp = Template("""\t{
\t\t${full_type} val = 0;
\t\tif (simdjson::SUCCESS != js["${key}"].get(val) || !js["${key}"].is_number()) {
\t\t\tif (${required}) { std::cerr << "not find [${key}]" << std::endl; }
\t\t\t\ttst.${key} = ${default_value};
\t\t\t} else { tst.${key} = static_cast<${type}>(val);
\t\t}
\t}
""")

get_str_value_tp = Template("""\t{
\t\tconst char* val = nullptr;
\t\tif (simdjson::SUCCESS != js["${key}"].get(val) || !js["${key}"].is_string() || !val) {
\t\t\tif (${required}) { std::cerr << "not find [${key}]" << std::endl; }
\t\t\tconst char* d = "${default_value}";
\t\t\tif (d) { tst.${key} = d; }
\t\t} else { tst.${key} = val; }
\t}
""")

get_list_bool_value_tp = Template("""\t{
\t\tsimdjson::dom::array array;
\t\tif (simdjson::SUCCESS != js["${key}"].get(array) || !js["${key}"].is_array()) {
\t\t\tif (${required}) { std::cerr << "not find [${key}]" << std::endl; }
\t\t} else {
\t\t\tsize_t len = array.size();
\t\t\tfor (size_t i = 0; i < len; i++) {
\t\t\t\tbool val = false;
\t\t\t\tif (array.at(i).is_bool()) { if (simdjson::SUCCESS == array.at(i).get(val)) { tst.${key}.push_back(val); } }
\t\t\t}
\t\t}
\t}
""")

get_list_int_value_tp = Template("""\t{
\t\tsimdjson::dom::array array;
\t\tif (simdjson::SUCCESS != js["${key}"].get(array) || !js["${key}"].is_array()) {
\t\t\tif (${required}) { std::cerr << "not find [${key}]" << std::endl; }
\t\t} else {
\t\t\tsize_t len = array.size();
\t\t\tfor (size_t i = 0; i < len; i++) {
\t\t\t\t${full_type} val = 0;
\t\t\t\tif (array.at(i).is_number()) { if (simdjson::SUCCESS == array.at(i).get(val)) { tst.${key}.push_back(static_cast<${subtype}>(val)); } }
\t\t\t}
\t\t}
\t}
""")

get_list_str_value_tp = Template("""\t{
\t\tsimdjson::dom::array array;
\t\tif (simdjson::SUCCESS != js["${key}"].get(array) || !js["${key}"].is_array()) {
\t\t\tif (${required}) { std::cerr << "not find [${key}]" << std::endl; }
\t\t} else {
\t\t\tsize_t len = array.size();
\t\t\tfor (size_t i = 0; i < len; i++) {
\t\t\t\tconst char* val = nullptr;
\t\t\t\if (array.at(i).is_string()) { if (simdjson::SUCCESS == array.at(i).get(val) && val) { tst.${key}.push_back(val); } }
\t\t\t}
\t\t}
\t}
""")

get_list_object_value_tp = Template("""\t{
\t\tsimdjson::dom::array array;
\t\tif (simdjson::SUCCESS != js["${key}"].get(array) || !js["${key}"].is_array()) {
\t\t\tif (${required}) { std::cerr << "not find [${key}]" << std::endl; }
\t\t} else {
\t\t\tsize_t len = array.size();
\t\t\tfor (size_t i = 0; i < len; i++) {
\t\t\t\tsimdjson::dom::element val;
\t\t\t\tif (array.at(i).is_object()) {
\t\t\t\t\tif (simdjson::SUCCESS == array.at(i).get(val)) {
\t\t\t\t\t\t${subtype} o;
\t\t\t\t\t\tif (json2struct(val, o)) { tst.${key}.push_back(o); }
\t\t\t\t\t}
\t\t\t\t}
\t\t\t}
\t\t}
\t}
""")

get_object_value_tp = Template("""\t{
\t\tsimdjson::dom::element val;
\t\tif (simdjson::SUCCESS != js["${key}"].get(val) || !js["${key}"].is_object()) {
\t\t\tif (${required}) { std::cerr << "not find [${key}]" << std::endl; }
\t\t} else {
\t\t\t${subtype} o;
\t\t\tif (json2struct(val, o)) { tst.${key} = o; }
\t\t}
\t}
""")

def template_enum_if_decl(name: str):
    return enum_if_decl.substitute(name=name)


def get_ns(ns: str) -> (str, str):
    ns_head = str()
    ns_tail = str()
    temp = ns.split('.')
    ns_code = str()
    if temp:
        # 命名空间
        for i in temp:
            ns_code = f'{ns_code}namespace {i} {{ '
        ns_head = ns_code
        ns_code = str()
        for i in temp:
            ns_code = f'{ns_code}}}'
        ns_tail = ns_code
    return ns_head, ns_tail


def is_enum_file(filename: str) -> bool:
    ret = re.match(r'.*?/e_.*?.proto', filename)
    ret2 = re.match(r'e_.*?.proto', filename)
    if ret or ret2:
        return True
    else:
        return False


def enum_define_header_filename(name: str) -> str:
    ret = re.sub(r'proto', r'pm.h', name)
    if ret:
        return ret
    else:
        return str()


def enum_if_header_filename(name: str) -> str:
    ret = re.sub(r'proto', r'if.h', name)
    if ret:
        return ret
    else:
        return str()


def enum_cpp_filename(name: str) -> str:
    ret = re.sub(r'proto', r'pm.cpp', name)
    if ret:
        return ret
    else:
        return str()


class EnumNode:
    def __init__(self, name, value: str = None, string: str = None, desc: str = None) -> None:
        # 枚举名
        self.name = name
        # 枚举值
        self.value = value
        # 枚举对应的字符串，未指定时使用枚举名
        self.string = string
        # 注释
        self.desc = desc
        if not self.string:
            self.string = string


def enum_string(e: EnumNode) -> str:
    if e.desc:
        ret = re.findall(r'\[str:(.*?)\]', e.desc)
        if ret:
            return ret[0]

    return e.name


class EnumDef:
    def __init__(self, name, desc: str = None):
        # 枚举类型名
        self.name = name
        # 枚举类型注释
        self.desc = desc
        # 枚举值
        self.enums: List[EnumNode] = list()
        # 枚举值的字符串格式集合
        self.enum_str_set: Set[str] = set()


class EnumFile:
    def __init__(self, filename: str, ns: str = None, desc: str = None):
        # 文件名
        self.filename = filename
        self.def_header = enum_define_header_filename(filename)
        self.if_header = enum_if_header_filename(filename)
        self.cpp_file = enum_cpp_filename(filename)
        # 命名空间
        self.ns = ns
        self.ns_head = str()
        self.ns_tail = str()
        if ns:
            self.ns_head, self.ns_tail = get_ns(ns)
        # 注释
        self.desc = desc
        if not self.desc:
            self.desc = str()
        # 枚举类型列表
        self.enum_defs: List[EnumDef] = list()
        # 枚举定义头文件
        self.code_def_header = str()
        # 接口头文件
        self.code_if_header = str()
        # 实现文件
        self.code_cxx = str()


class GlobalEnum:
    # 全局枚举类型名列表
    enums_set: Dict[str, str] = dict()
    # 枚举文件
    enum_files: List[EnumFile] = list()


class StructNode:
    def __init__(self, name: str, node_type: str, desc: str = None, value: str = None, sub_type: str = None):
        self.name = name
        self.desc = desc
        self.def_value = value
        self.type = node_type
        self.sub_type = sub_type
        ret = re.findall(r'\[type:(.*?)\]', desc)
        real_type = str()
        if ret:
            real_type = ret[0]

        # 默认值
        ret = re.findall(r'\[eg:(.*?)\]', desc)
        def_value = str()
        if ret:
            def_value = ret[0]

        # 纠正类型
        # 整形
        if node_type == "int32" or node_type == "uint32" or node_type == "int64" or node_type == "uint64":
            if real_type in GlobalCode.support_int.keys():
                self.type = GlobalCode.support_int[real_type]
            else:
                self.type = GlobalCode.support_int[self.type]
            if def_value:
                if not isinstance(eval(def_value), int):
                    print(f'[ERROR] int default value: {def_value}')
                self.def_value = def_value
            else:
                self.def_value = "0"
        # 浮点型
        elif node_type == "float" or node_type == "double":
            if real_type in GlobalCode.support_float.keys():
                self.type = GlobalCode.support_int[real_type]
            if def_value:
                if not isinstance(eval(def_value), float):
                    print(f'[ERROR] float default value: {def_value}')
                self.def_value = def_value
            else:
                self.def_value = "0.0"
        # 布尔
        elif node_type == "bool":
            self.type = "bool"
            if def_value:
                if def_value != "true" and def_value != "false":
                    print(f'[ERROR] bool default value: {def_value}')
                    exit(-1)
                self.def_value = def_value
            else:
                self.def_value = "false"
        # 字符串
        elif node_type == "string":
            self.type = "string"
            if def_value:
                self.def_value = def_value
            else:
                self.def_value = ""
        # 数组
        elif node_type == "list":
            self.type = "vector"
            # 子类型
            # 整形
            if sub_type == "int32" or sub_type == "uint32" or sub_type == "int64" or sub_type == "uint64":
                if real_type in GlobalCode.support_int.keys():
                    self.sub_type = GlobalCode.support_int[real_type]
                else:
                    self.sub_type = GlobalCode.support_int[self.sub_type]
            # 浮点型
            elif sub_type == "float" or sub_type == "double":
                if real_type in GlobalCode.support_float.keys():
                    self.sub_type = GlobalCode.support_int[real_type]
            # 布尔
            elif sub_type == "bool":
                self.sub_type = "bool"
            # 字符串
            elif sub_type == "string":
                self.sub_type = "string"
            else:
                # 结构体/枚举
                pass
        else:
            # 结构体/枚举
            pass


class StructDef:
    def __init__(self, name, desc):
        self.name = name
        self.desc = desc
        self.members: List[StructNode] = list()


class StructFile:
    def __init__(self, filename: str, ns: str = None, desc: str = None):
        # 文件名
        self.filename = filename
        self.def_header = enum_define_header_filename(filename)
        self.if_header = enum_if_header_filename(filename)
        self.cpp_file = enum_cpp_filename(filename)
        # 命令空间
        self.ns = ns
        self.ns_head = str()
        self.ns_tail = str()
        if ns:
            self.ns_head, self.ns_tail = get_ns(ns)
        self.desc = desc
        if not self.desc:
            self.desc = str()
        # 引用头文件，为依赖的枚举或其他结构体文件
        self.import_headers: Set[str] = set()
        # 结构体列表
        self.struct_list: List[StructDef] = list()
        # 结构体声明头文件代码
        self.code_def_header = str()
        # 结构体结构体声明头文件代码
        self.code_if_header = str()
        # 结构实现带代码
        self.code_def_cxx = str()


class GlobalStruct:
    # 结构体定义集合，不能冲突
    struct_set: Dict[str, str] = dict()
    # 结构体文件列表
    struct_file: List[StructFile] = list()


class TypeMap:
    def __init__(self, protobuf_type: str, cxx_type: str):
        self.proto_type = protobuf_type
        self.cxx_type = cxx_type


class GlobalCode:
    json_ctx = dict()
    out_dir = str()
    global_enum = GlobalEnum()
    global_struct = GlobalStruct()
    support_int = {
        "int8": "int8_t",
        "uint8": "uint8_t",
        "int16": "int16_t",
        "uint16": "uint16_t",
        "int32": "int32_t",
        "uint32": "uint32_t",
        "int64": "int64_t",
        "uint64": "uint64_t"
    }
    support_float = {
        "float": "float",
        "double": "double"
    }
    support_bool = {"bool": "bool"}
    support_string = {"string": "sting"}
    support_list = {"repeat": "vector"}
    support_map = {"map": "map"}
    support_map_key = ("int", "string", "enum")
    base_type = set()
    for value in support_int.values():
        base_type.add(value)
    for value in support_float.values():
        base_type.add(value)
    for value in support_bool.values():
        base_type.add(value)
    int_type = ["int8_t", "int16_t", "int32_t", "int64_t"]
    uint_type = ["uint8_t", "uint16_t", "uint32_t", "uint64_t"]
    float_type = ["float", "double"]
    int8_max = "INT8_MAX"
    uint8_max = "UINT8_MAX"
    int16_max = "INT16_MAX"
    uint16_max = "UINT16_MAX"
    int32_max = "INT32_MAX"
    uint32_max = "UINT32_MAX"
    int64_max = "INT64_MAX"
    uint64_max = "UINT64_MAX"


def gen_enum_code():
    for file in GlobalEnum.enum_files:
        # 创建目录
        dir_path = os.path.dirname(file.def_header)
        os.makedirs(dir_path, exist_ok=True)
        # 枚举定义头文件
        file.code_def_header = f'#pragma once\n\n'
        file.code_if_header = f'#pragma once\n\n#include "{os.path.basename(file.def_header)}"'
        file.code_cxx = f'#include "{os.path.basename(file.if_header)}"\n\n'
        # 加注释
        if file.desc:
            file.code_def_header = f'// {file.desc}\n{file.code_def_header}\n'
            file.code_if_header = f'// {file.desc}\n{file.code_if_header}\n'
            file.code_cxx = f'// {file.desc}\n{file.code_cxx}\n'

        # 模板声明
        file.code_if_header = f'{file.code_if_header}\n{enum_if_template.substitute(head=file.ns_head, end=file.ns_tail)}\n'

        # 加命名空间
        if file.ns_head:
            file.code_def_header = f'{file.code_def_header}\n{file.ns_head}\n\n'
            file.code_if_header = f'{file.code_if_header}\n{file.ns_head}\n\n'
            file.code_cxx = f'{file.code_cxx}\n{file.ns_head}\n\n'

        # 枚举定义头文件代码
        def_code = str()
        for e in file.enum_defs:
            # 枚举定义头文件
            # 枚举接口头文件
            # 枚举字符串映射

            # 枚举类型
            def_code = f'\nenum class {e.name} {{\n'
            # 接口声明
            if_code = f'{template_enum_if_decl(e.name)}'
            # 反射接口实现
            cxx_ref_code = f'template <> const char* get_enum_as_str<{e.name}>({e.name} e) {{\n\tswitch(e) {{\n'
            # 自定义映射字符串接口实现
            cxx_str_code = f'template <> const char* get_enum_str<{e.name}>({e.name} e) {{\n\tswitch(e) {{\n'
            # 字符串查询枚举
            cxx_find_code = f'template <> {e.name} get_enum_value<{e.name}>(const char* str) {{\n\tstatic std::map<std::string, {e.name}> emap = {{\n'
            # 范围判定
            cxx_range_code = f'template <> bool in_enum_range<{e.name}>({e.name} e) {{\n\tswitch(e) {{\n'

            # 注释
            if e.desc:
                def_code = f'// {e.desc}{def_code}'

            # 有枚举值
            cxx_ref_temp = str()
            cxx_str_temp = str()
            cxx_find_temp = str()
            cxx_range_temp = str()
            for value in e.enums:
                # 单条枚举值
                single = f'{value.name}'
                single = f'{single:36s} = {value.value},'
                if value.desc:
                    single = f'{single:62s}///< {value.desc}\n'
                else:
                    single = f'{single:62s}///< {value.string}\n'
                # 追加到枚举代码
                def_code = f'{def_code}\t{single}'

                # 接口
                name = f'{value.name}:'
                cxx_ref_temp = f'{cxx_ref_temp}\t\tcase {e.name}::{name:32s} return "{e.name}::{value.name}";\n'
                cxx_str_temp = f'{cxx_str_temp}\t\tcase {e.name}::{name:32s} return "{value.string}";\n'
                cxx_range_temp = f'{cxx_range_temp}\t\tcase {e.name}::{name:32s} return true;\n'

                name = f'"{value.string}",'
                cxx_find_code = f'{cxx_find_code}\t\t{{{name:48s}{e.name}::{value.name}}},\n'
            # 结束符
            def_code = f'{def_code}}};\n'
            cxx_ref_code = f'{cxx_ref_code}{cxx_ref_temp}\t\tdefault: return nullptr;\n\t}}\n}}\n\n'
            cxx_str_code = f'{cxx_str_code}{cxx_str_temp}\t\tdefault: return nullptr;\n\t}}\n}}\n\n'
            cxx_find_code = f'{cxx_find_code}{cxx_find_temp}\t}};\n\n\tif (!str) {{ if (sizeof({e.name}) < sizeof(uint32_t)) {{ return static_cast<{e.name}>({GlobalCode.uint64_max}); }} else {{ return static_cast<{e.name}>({GlobalCode.uint64_max}); }} }}\n\n\tauto key = emap.find(str);\n\n\tif (emap.end() == key) {{ if (sizeof({e.name}) < sizeof(uint64_t)) {{ return static_cast<{e.name}>({GlobalCode.uint32_max}); }} else {{ return static_cast<{e.name}>({GlobalCode.uint64_max}); }} }}\n\n\treturn key->second;\n}}\n\n'
            cxx_range_code = f'{cxx_range_code}{cxx_range_temp}\t\tdefault: return false;\n\t}}\n}}\n\n'

            # 追加到文件内容
            file.code_def_header = f'{file.code_def_header}{def_code}'
            file.code_cxx = f'{file.code_cxx}{cxx_ref_code}{cxx_str_code}{cxx_find_code}{cxx_range_code}'
            file.code_if_header = f'{file.code_if_header}{if_code}'
        if file.ns_tail:
            file.code_def_header = f'{file.code_def_header}\n{file.ns_tail}\n'
            file.code_cxx = f'{file.code_cxx}\n{file.ns_tail}\n'
            file.code_if_header = f'{file.code_if_header}\n{file.ns_tail}\n'
        # 写入文件
        with open(file.def_header, 'w') as f:
            f.write(file.code_def_header)
        with open(file.if_header, 'w') as f:
            f.write(file.code_if_header)
        with open(file.cpp_file, 'w') as f:
            f.write(file.code_cxx)


def gen_struct_code():
    for file in GlobalStruct.struct_file:
        # 创建目录
        dir_path = os.path.dirname(file.def_header)
        os.makedirs(dir_path, exist_ok=True)
        file.code_def_header = f'#pragma once\n\n#include <vector>\n#include <string>\n#include <stdint.h>\n'
        file.code_if_header = f'#pragma once\n\n#include "{os.path.basename(file.def_header)}"'
        file.code_cxx = f'#include "{os.path.basename(file.if_header)}"\n\n'
        # 结构体定义头文件正文
        code_def_ctx = str()
        # 结构体声明
        type_decl = str()
        # 依赖关系
        depend: list[Dict[str, Dict[str]]] = list()
        file_struct = set()

        # 加注释
        if file.desc:
            file.code_def_header = f'// {file.desc}\n{file.code_def_header}\n'
            file.code_if_header = f'// {file.desc}\n{file.code_if_header}\n'
            file.code_cxx = f'// {file.desc}\n{file.code_cxx}\n'
        # 接口声明
        file.code_if_header = f'{file.code_if_header}\n{struct_if_template.substitute(head=file.ns_head, end=file.ns_tail)}\n'

        # 加命名空间
        if file.ns_head:
            file.code_if_header = f'{file.code_if_header}\n{file.ns_head}\n\n'
            file.code_cxx = f'{file.code_cxx}\n{file.ns_head}\n\n'

        # 代码生成
        temp_list = reversed(file.struct_list)
        for s in temp_list:
            file_struct.add(s.name)
            # 接口声明
            file.code_if_header = f'{file.code_if_header}template <> bool json2struct<{s.name}>(simdjson::dom::element &js, {s.name} &st);\n'
            file.code_if_header = f'{file.code_if_header}template <> bool struct2json<{s.name}>(const {s.name} &st, nlohmann::json &js);\n'

            # 接口实现代码
            json2struct_code = f'template <> bool json2struct<{s.name}>(simdjson::dom::element &js, {s.name} &st) {{\n\t{s.name} tst;\n'
            struct2json_code = f'template <> bool struct2json<{s.name}>(const {s.name} &st, nlohmann::json &js) {{\n'

            # 结构体代码
            member_code = f'struct {s.name}_s {{\n'
            type_decl = f'{type_decl}typedef struct {s.name}_s {s.name};\n'
            t = {
                s.name: {
                    "depend": [],
                    "code": str()
                }
            }

            # 构造函数代码
            constructor_code = f'\t{s.name}_s() {{'
            # 注释
            if s.desc:
                member_code = f'// {s.desc}\n{member_code}'
            for m in s.members:
                # 数组
                if m.type == vector:
                    code = f'std::vector<{m.sub_type}> {m.name};'
                    if m.sub_type not in GlobalCode.base_type and m.sub_type != string:
                        # 记录依赖的结构体
                        if m.sub_type not in GlobalStruct.struct_set.keys() and m.sub_type not in GlobalEnum.enums_set.keys():
                            print(f'[ERROR] not find such object: "{m.sub_type}"')
                            exit(-1)
                        t[s.name]["depend"].append(m.sub_type)
                        if GlobalStruct.struct_set.__contains__(m.sub_type) and GlobalStruct.struct_set[m.sub_type] not in file.import_headers:
                            file.import_headers.add(GlobalStruct.struct_set[m.sub_type])
                        if GlobalEnum.enums_set.__contains__(m.sub_type):
                            file.import_headers.add(GlobalEnum.enums_set[m.sub_type])
                # 数字
                elif m.type in GlobalCode.base_type:
                    code = f'{m.type} {m.name};'
                    constructor_code = f'{constructor_code}\n\t\t{m.name} = {m.def_value};'
                # 字符串
                elif m.type == string:
                    code = f'std::{m.type} {m.name};'
                    constructor_code = f'{constructor_code}\n\t\t{m.name} = "{m.def_value}";'
                # 枚举
                elif m.type in GlobalEnum.enums_set.keys():
                    code = f'{m.type} {m.name};'
                    if m.def_value:
                        constructor_code = f'{constructor_code}\n\t\t{m.name} = {m.def_value};'
                    file.import_headers.add(GlobalEnum.enums_set[m.type])
                # 结构体
                else:
                    if m.type not in GlobalStruct.struct_set.keys():
                        print(f'[ERROR] not find such object: "{m.type}"')
                        exit(-1)
                    # 记录依赖的结构体
                    t[s.name]["depend"].append(m.type)
                    if GlobalStruct.struct_set.__contains__(m.type) and GlobalStruct.struct_set[m.type] not in file.import_headers:
                        file.import_headers.add(GlobalStruct.struct_set[m.type])
                    code = f'{m.type} {m.name};'

                # 加注释
                if m.desc:
                    code = f'\t{code:64s}///< {m.desc}\n'
                else:
                    code = f'\t{code}\n'
                member_code = f'{member_code}{code}'

                # 结构体转json
                # 基本类型
                if m.type in GlobalCode.base_type or m.type == string or m.type in GlobalEnum.enums_set.keys():
                    struct2json_code = f'{struct2json_code}{convert_nor_tp.substitute(key=m.name)}\n'
                # 数组
                elif m.type == vector:
                    # 子类型为基本类型
                    if m.sub_type in GlobalCode.base_type or m.sub_type == string or m.sub_type in GlobalEnum.enums_set.keys():
                        struct2json_code = f'{struct2json_code}{convert_list_nor_tp.substitute(key=m.name)}\n'
                    else:
                        struct2json_code = f'{struct2json_code}{convert_list_object_tp.substitute(key=m.name)}\n'
                # 结构体
                else:
                    struct2json_code = f'{struct2json_code}{convert_object_tp.substitute(key=m.name)}\n'

                # json转结构体

                # 有符号整型
                if m.type in GlobalCode.int_type:
                    json2struct_code = f'{json2struct_code}{get_int_value_tp.substitute(full_type=int64_t, key=m.name, required="false", default_value=m.def_value, type=m.type)} '
                # 无符号整型
                elif m.type in GlobalCode.uint_type:
                    json2struct_code = f'{json2struct_code}{get_int_value_tp.substitute(full_type=uint64_t, key=m.name, required="false", default_value=m.def_value, type=m.type)} '
                # 浮点
                elif m.type in GlobalCode.float_type:
                    json2struct_code = f'{json2struct_code}{get_int_value_tp.substitute(full_type="double", key=m.name, required="false", default_value=m.def_value, type=m.type)} '
                # bool
                elif m.type in GlobalCode.support_bool.values():
                    json2struct_code = f'{json2struct_code}{get_bool_value_tp.substitute(key=m.name, required="false", default_value=m.def_value)} '
                # 字符串
                elif m.type == string:
                    json2struct_code = f'{json2struct_code}{get_str_value_tp.substitute(key=m.name, required="false", default_value=m.def_value)} '
                # 枚举
                elif m.type in GlobalEnum.enums_set.keys():
                    json2struct_code = f'{json2struct_code}{get_int_value_tp.substitute(full_type=uint64_t, key=m.name, required="false", default_value=f"static_cast<{m.type}>(0)", type=m.type)} '
                # 数组
                elif m.type == vector:
                    if m.sub_type in GlobalCode.int_type:
                        json2struct_code = f'{json2struct_code}{get_list_int_value_tp.substitute(full_type=int64_t, key=m.name, required="false", subtype=m.sub_type)}'
                    elif m.sub_type in GlobalCode.uint_type or m.sub_type in GlobalEnum.enums_set.keys():
                        json2struct_code = f'{json2struct_code}{get_list_int_value_tp.substitute(full_type=uint64_t, key=m.name, required="false", subtype=m.sub_type)}'
                    elif m.sub_type in GlobalCode.float_type:
                        json2struct_code = f'{json2struct_code}{get_list_int_value_tp.substitute(full_type="double", key=m.name, required="false", subtype=m.sub_type)}'
                    elif m.sub_type in GlobalCode.support_bool.values():
                        json2struct_code = f'{json2struct_code}{get_list_bool_value_tp.substitute(key=m.name, required="false")} '
                    elif m.sub_type == string:
                        json2struct_code = f'{json2struct_code}{get_list_str_value_tp.substitute(key=m.name, required="false")}'
                    # elif m.sub_type in GlobalEnum.enums_set.keys():
                    #     json2struct_code = f'{json2struct_code}{get_list_int_value_tp.substitute(full_type=uint64_t, key=m.name, required="false", subtype=m.sub_type)}'
                    else:
                        json2struct_code = f'{json2struct_code}{get_list_object_value_tp.substitute(key=m.name, required="false", subtype=m.sub_type)}'
                # 结构体
                else:
                    json2struct_code = f'{json2struct_code}{get_object_value_tp.substitute(key=m.name, required="false", subtype=m.type)}'

            # 追加到正文
            # code_def_ctx = f'{code_def_ctx}{member_code}{constructor_code}\n\t}}\n}};\n\n'
            t[s.name]["code"] = f'{member_code}{constructor_code}\n\t}}\n}};\n\n'
            file.code_cxx = f'{file.code_cxx}{struct2json_code}\n\treturn true;\n}}\n\n{json2struct_code}\n\tst = tst;\n\treturn true;\n}}\n\n'
            depend.append(t)

        # 引用头文件
        import_headers = '#include <iostream>\n'
        for item in file.import_headers:
            if item not in file.filename:
                import_headers = f'{import_headers}#include "{item}"\n'

        if import_headers:
            file.code_def_header = f'{file.code_def_header}{import_headers}'

        # 加命名空间
        if file.ns_head:
            file.code_def_header = f'{file.code_def_header}\n{file.ns_head}\n\n'

        # 依赖的结构体排序
        result_list = list()
        for item in depend:
            max_idx = -1
            for k, v in item.items():
                cur_name = k
                for i in v["depend"]:
                    if i in file_struct:
                        try:
                            idx = result_list.index(i)
                        except Exception as e:
                            idx = -1
                        if idx > max_idx:
                            max_idx = idx
                if max_idx == -1:
                    result_list.insert(0, cur_name)
                else:
                    result_list.insert(max_idx + 1, cur_name)

        # 生成代码正文
        for i in result_list:
            for j in depend:
                for k, v in j.items():
                    if k == i:
                        code_def_ctx = f'{code_def_ctx}{v["code"]}'
        file.code_def_header = f'{file.code_def_header}{type_decl}\n{code_def_ctx}'

        if file.ns_tail:
            file.code_def_header = f'{file.code_def_header}\n{file.ns_tail}\n'
            file.code_cxx = f'{file.code_cxx}\n{file.ns_tail}\n'
            file.code_if_header = f'{file.code_if_header}\n{file.ns_tail}\n'
        # 写文件
        with open(file.def_header, 'w') as f:
            f.write(file.code_def_header)
        with open(file.if_header, 'w') as f:
            f.write(file.code_if_header)
        with open(file.cpp_file, 'w') as f:
            f.write(file.code_cxx)


def gen_enum_file(file_desc: dict):
    # 文件路径
    filepath = os.path.join(GlobalCode.out_dir, file_desc["name"])
    # 枚举文件信息
    enum_file = EnumFile(filepath, ns=file_desc["package"], desc=file_desc["description"])
    # 添加到枚举文件信息列表
    GlobalEnum.enum_files.append(enum_file)

    for enum in file_desc["enums"]:
        # 枚举类型定义
        enum_def = EnumDef(enum["name"], desc=enum["description"])
        # 添加到枚举类型集合
        GlobalEnum.enums_set[enum["name"]] = enum_define_header_filename(file_desc["name"])
        # 枚举值
        for value in enum["values"]:
            enum_node = EnumNode(value["name"], value=value["number"], desc=value["description"])
            # 添加到枚举值列表
            enum_def.enums.append(enum_node)
            # 字符串集合，字符串从注释里得到，需要自己检测冲突
            enum_str = f'{enum_def.name}::{enum_string(enum_node)}'
            if enum_str in enum_def.enum_str_set:
                print(f'[ERROR]{enum_def.name}::{enum_node.name} --> "{enum_str}" conflict')
                exit(-1)
            enum_node.string = enum_str
            enum_def.enum_str_set.add(enum_str)
        # 添加枚举类型定义
        enum_file.enum_defs.append(enum_def)
    gen_enum_code()


def gen_struct_file(file_desc: dict):
    # 文件路径
    filepath = os.path.join(GlobalCode.out_dir, file_desc["name"])
    # 枚举文件信息
    st_file = StructFile(filepath, ns=file_desc["package"], desc=file_desc["description"])
    # 添加到枚举文件信息列表
    GlobalStruct.struct_file.append(st_file)

    for st in file_desc["messages"]:
        # 结构体定义
        st_def = StructDef(st["name"], desc=st["description"])
        # 添加到结构体类型集合
        GlobalStruct.struct_set[st["name"]] = enum_define_header_filename(file_desc["name"])
        for member in st["fields"]:
            # 数组
            if member["label"] == "repeated" and not re.match(r'Map.*?Enrty', member["type"]):
                st_node = StructNode(member["name"], "list", desc=member["description"], sub_type=member["type"])
            else:
                st_node = StructNode(member["name"], member["type"], desc=member["description"])
            st_def.members.append(st_node)
        st_file.struct_list.append(st_def)


def gen_enum() -> None:
    files = GlobalCode.json_ctx["files"]
    for file in files:
        if is_enum_file(file["name"]):
            gen_enum_file(file)


def gen_struct() -> None:
    files = GlobalCode.json_ctx["files"]
    for file in files:
        if not is_enum_file(file["name"]):
            gen_struct_file(file)
    gen_struct_code()


def gen_protobuf_json_2_cpp() -> None:
    GlobalCode.json_ctx = json.load(open(args.path, 'r'))
    GlobalCode.out_dir = args.out
    gen_enum()
    gen_struct()


# Press the green button in the gutter to run the script.
if __name__ == '__main__':
    gen_protobuf_json_2_cpp()
