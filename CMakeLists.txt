cmake_minimum_required(VERSION 3.6)

set(TARGET biot)
# 主版本
set(BIOT_MAJOR_VERSION 1)
# 次版本
set(BIOT_MINOR_VERSION 0)
# 补丁版本
set(BIOT_PATCH_VERSION 0)
set(BIOT_VERSION "${BIOT_MAJOR_VERSION}.${BIOT_MINOR_VERSION}.${BIOT_PATCH_VERSION}")
# 发布版本日期，该日期为该版本的开始开发日期
set(BIOT_BASE_VERSION 22020402)

# 软件阶段版本
# base:架构版本，无实际功能
# alpha:内部功能版本，bug很多
# beta:无严重错误版本
# rc:基本成熟的版本
# release:发布版本
if("${BIOT_PERIOD_VERSION}" STREQUAL "base")
    set(BIOT_PERIOD_VERSION "base")
elseif("${BIOT_PERIOD_VERSION}" STREQUAL "alpha")
    set(BIOT_PERIOD_VERSION "alpha")
elseif("${BIOT_PERIOD_VERSION}" STREQUAL "rc")
    set(BIOT_PERIOD_VERSION "rc")
elseif("${BIOT_PERIOD_VERSION}" STREQUAL "release")
    set(BIOT_PERIOD_VERSION "release")
else()
    set(BIOT_PERIOD_VERSION "beta")
endif()

message(STATUS "BIOT_VERSION=${BIOT_VERSION}")
message(STATUS "BIOT_PERIOD_VERSION=${BIOT_PERIOD_VERSION}")

# 工程名
project(${TARGET} VERSION ${BIOT_MAJOR_VERSION}.${BIOT_MINOR_VERSION}.${BIOT_PATCH_VERSION})

# 标准
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED True)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# 是否debug，通过-DCMAKE_BUILD_TYPE=Debug来指定，默认standard
message(STATUS "CMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}")

if("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -W -Wall -O0 -g")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -W -Wall -O0 -g")
	set(BIOT_EDITION "debug")
    add_definitions(-DDEBUG)
else()
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -W -Wall -O3")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -W -Wall -O3")
	set(BIOT_EDITION "standard")
    message(STATUS "standard version")
    add_definitions(-DNDEBUG)
endif()

# 编译选项
set(BIOT_FLAGS " -pipe")
set(BIOT_FLAGS "${BIOT_FLAGS} -fPIC")
set(BIOT_FLAGS "${BIOT_FLAGS} -Wno-unused-parameter")
set(BIOT_FLAGS "${BIOT_FLAGS} -Wno-builtin-macro-redefined")
set(BIOT_FLAGS "${BIOT_FLAGS} -fno-omit-frame-pointer")
set(BIOT_FLAGS "${BIOT_FLAGS} -Wno-implicit-fallthrough")
set(BIOT_FLAGS "${BIOT_FLAGS} -fstack-protector-all")
set(BIOT_FLAGS "${BIOT_FLAGS} -Wno-deprecated-declarations")
set(BIOT_FLAGS "${BIOT_FLAGS} -Wno-class-memaccess")
set(BIOT_FLAGS "${BIOT_FLAGS} -Wno-maybe-uninitialized")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${BIOT_FLAGS}")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${BIOT_FLAGS}")

# 编译宏
add_definitions(-D__const__=__unused__ -DLANGUAGE_ZH -DWITH_OPENSSL -DWITH_ZLIB -DJM_CIRCULAR_BUFFER_CXX_14)

# 执行系统命令，获取宏的结果
execute_process(COMMAND date +"%A %Y-%m-%d %H:%M:%S %z" TIMEOUT 5 OUTPUT_VARIABLE BIOT_COMPILE_DATETIME OUTPUT_STRIP_TRAILING_WHITESPACE)
execute_process(COMMAND date +"%Y%m%d%H%M" TIMEOUT 5 OUTPUT_VARIABLE BIOT_DATE_VERSION OUTPUT_STRIP_TRAILING_WHITESPACE)
execute_process(COMMAND /usr/bin/cat /proc/sys/kernel/random/uuid TIMEOUT 5 OUTPUT_VARIABLE BIOT_UUID OUTPUT_STRIP_TRAILING_WHITESPACE)

message(STATUS "compile time:BIOT_COMPILE_DATETIME=${BIOT_COMPILE_DATETIME}")
message(STATUS "compile date:BIOT_DATE_VERSION=${BIOT_DATE_VERSION}")
message(STATUS "compile uuid:BIOT_UUID=${BIOT_UUID}")

message(STATUS "gen biot_configure.h")
# 生成配置
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/biot_configure.h.in ${CMAKE_CURRENT_SOURCE_DIR}/biot_configure.h)

set(INCDIR include)
set(SRCDIR src)
set(LIBDIR lib)
set(BINDIR bin)

# 链接库
set(BIOT_LIBS -lhv_static)
set(BIOT_LIBS ${BIOT_LIBS} -lhw-iot-dev-access)
set(BIOT_LIBS ${BIOT_LIBS} -lspdlog)
set(BIOT_LIBS ${BIOT_LIBS} -lsimdjson)
set(BIOT_LIBS ${BIOT_LIBS} -lpaho-mqtt3a -lpaho-mqtt3as -lpaho-mqtt3c -lpaho-mqtt3cs)
set(BIOT_LIBS ${BIOT_LIBS} -loatpp)
set(BIOT_LIBS ${BIOT_LIBS} -lprotobuf)
set(BIOT_LIBS ${BIOT_LIBS} -lz -lssl -lcrypto -lpthread -ldl -lrt)

message(STATUS "use libs: ${BIOT_LIBS}")

# 头文件目录
set(INCDIRS . include src include/oatpp-1.3.0/oatpp)
set(INCDIRS ${INCDIRS} src/module/network/netapp)
# set(INCDIRS ${INCDIRS} src/module/network/netapp/web)
# 链接目录
set(LIBDIRS . lib lib/oatpp-1.3.0)
include_directories(${INCDIRS} ${SRCDIR})
link_directories(${LIBDIRS})

macro(list_source_directories srcs)
    unset(tmp)
    foreach(dir ${ARGN})
        aux_source_directory(${dir} tmp)
    endforeach()
    set(${srcs} ${tmp})
    list(FILTER ${srcs} EXCLUDE REGEX ".*_test\\.c")
endmacro()

macro(glob_headers_and_sources files)
    unset(tmp)
    foreach(dir ${ARGN})
        file(GLOB tmp ${dir}/*.h ${dir}/*.c ${dir}/*.hpp ${dir}/*.cpp ${dir}/*.cc)
        list(APPEND ${files} ${tmp})
    endforeach()
    list(FILTER ${files} EXCLUDE REGEX ".*_test\\.c")
endmacro()

#重新定义当前目标的源文件的__FILE__宏
function(redefine_file_macro targetname)
    #获取当前目标的所有源文件
    get_target_property(source_files "${targetname}" SOURCES)
    #遍历源文件
    foreach(sourcefile ${source_files})
        #获取当前源文件的编译参数
        get_property(defs SOURCE "${sourcefile}"
            PROPERTY COMPILE_DEFINITIONS)
        #获取当前文件的绝对路径
        get_filename_component(filepath "${sourcefile}" ABSOLUTE)
        #将绝对路径中的项目路径替换成空,得到源文件相对于项目路径的相对路径
        string(REPLACE ${PROJECT_SOURCE_DIR}/${SRCDIR} "" relpath ${filepath})
        #将我们要加的编译参数(__FILE__定义)添加到原来的编译参数里面
        list(APPEND defs "__FILE__=\"${relpath}\"")
        #重新设置源文件的编译参数
        set_property(
            SOURCE "${sourcefile}"
            PROPERTY COMPILE_DEFINITIONS ${defs}
            )
    endforeach()
endfunction()

set(BIOT_SRCDIRS src/)
# XX 越底层库越写在后边
# 网络
set(BIOT_SRCDIRS ${BIOT_SRCDIRS} src/module/network/netapp/web)
set(BIOT_SRCDIRS ${BIOT_SRCDIRS} src/module/network/netapp/web/compoent)
set(BIOT_SRCDIRS ${BIOT_SRCDIRS} src/module/network/netapp/web/contoller)
set(BIOT_SRCDIRS ${BIOT_SRCDIRS} src/module/network/netapp/web/dto)
set(BIOT_SRCDIRS ${BIOT_SRCDIRS} src/module/network/netbasic)

# 参数
set(BIOT_SRCDIRS ${BIOT_SRCDIRS} src/config/param/param_def/enums)
set(BIOT_SRCDIRS ${BIOT_SRCDIRS} src/config/param/param_patch)
set(BIOT_SRCDIRS ${BIOT_SRCDIRS} src/config/param/param_def)
# protobuf生成的代码不需要
# set(BIOT_SRCDIRS ${BIOT_SRCDIRS} src/config/param/param_pb)

# 源码目录
set(BIOT_SRCDIRS ${BIOT_SRCDIRS} src/config/param)
set(BIOT_SRCDIRS ${BIOT_SRCDIRS} src/config/capa/product)
set(BIOT_SRCDIRS ${BIOT_SRCDIRS} src/config/capa/common)
set(BIOT_SRCDIRS ${BIOT_SRCDIRS} src/config/capa)
set(BIOT_SRCDIRS ${BIOT_SRCDIRS} src/config)
set(BIOT_SRCDIRS ${BIOT_SRCDIRS} src/boot)

# basic
set(BIOT_SRCDIRS ${BIOT_SRCDIRS} src/basic/log)
set(BIOT_SRCDIRS ${BIOT_SRCDIRS} src/basic/base)
set(BIOT_SRCDIRS ${BIOT_SRCDIRS} src/basic/defs)
set(BIOT_SRCDIRS ${BIOT_SRCDIRS} src/basic)

# 查找源码
list_source_directories(BIOT_SRCS ${BIOT_SRCDIRS})

# 编译目标
add_executable(${TARGET} ${BIOT_SRCS})

# 链接库
target_link_libraries(${TARGET} ${BIOT_LIBS})

# 替换__FILE__为相对路径
redefine_file_macro(${TARGET})

# TODO:打包

# 查看完整的编译选项
# cmake --build . -- VERBOSE=1