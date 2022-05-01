cmake_minimum_required(VERSION 3.6)

set(TARGET biot)
# 主版本
set(BIOT_MAJOR_VERSION 1)
# 次版本
set(BIOT_MINOR_VERSION 0)
# 发布版本
set(BIOT_RELEASE_VERSION 0)
set(BIOT_VERSION "${BIOT_MAJOR_VERSION}.${BIOT_MINOR_VERSION}.${BIOT_RELEASE_VERSION}")
# 发布版本日期，该日期为该版本的开始开发日期
set(BIOT_BASE_VERSION 22020402)

message(STATUS "application version=${BIOT_VERSION}")

# 工程名
project(${TARGET} VERSION ${BIOT_MAJOR_VERSION}.${BIOT_MINOR_VERSION}.${BIOT_RELEASE_VERSION})

# 标准
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED True)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# 是否debug，通过-DCMAKE_BUILD_TYPE=Debug来指定，默认release
message(STATUS "CMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}")

if("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
    set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -W -Wall -O0 -g")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -W -Wall -O0 -g")
	set(BIOT_EDITION "debug")
    add_definitions(-DDEBUG)
else()
    set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -W -Wall -O3")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -W -Wall -O3")
	set(BIOT_EDITION "release")
    add_definitions(-DNDEBUG)
endif()

# 编译选项
set(BIOT_FLAGS " -pipe -fPIC \
				-Wno-unused-parameter \
				-Wno-builtin-macro-redefined \
				-fno-omit-frame-pointer \
				-Wno-implicit-fallthrough \
				-fstack-protector-all \
				-Wno-deprecated-declarations \
				-Wno-class-memaccess \
				-Wno-unused-result \
				-Wno-maybe-uninitialized")

set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} ${BIOT_FLAGS}")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} ${BIOT_FLAGS}")

set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} ${BIOT_FLAGS}")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} ${BIOT_FLAGS}")

# 编译宏
add_definitions(-D__const__=__unused__ -DLANGUAGE_ZH -DWITH_OPENSSL -DWITH_ZLIB -DJM_CIRCULAR_BUFFER_CXX_14)

# 执行系统命令，获取宏的结果
execute_process(COMMAND date +"%A %Y-%m-%d %H:%M:%S %z" TIMEOUT 5 OUTPUT_VARIABLE BIOT_COMPILE_DATETIME OUTPUT_STRIP_TRAILING_WHITESPACE)
execute_process(COMMAND date +"%Y%m%d%H%M" TIMEOUT 5 OUTPUT_VARIABLE BIOT_DATE_VERSION OUTPUT_STRIP_TRAILING_WHITESPACE)
execute_process(COMMAND /usr/bin/cat /proc/sys/kernel/random/uuid TIMEOUT 5 OUTPUT_VARIABLE BIOT_UUID OUTPUT_STRIP_TRAILING_WHITESPACE)

message(STATUS "compile time=${BIOT_COMPILE_DATETIME}")
message(STATUS "compile date=${BIOT_DATE_VERSION}")
message(STATUS "compile uuid=${BIOT_UUID}")

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
set(BIOT_LIBS ${BIOT_LIBS} -lpaho-mqtt3a -lpaho-mqtt3as -lpaho-mqtt3c -lpaho-mqtt3cs)
set(BIOT_LIBS ${BIOT_LIBS} -loatpp)
set(BIOT_LIBS ${BIOT_LIBS} -lprotobuf)
set(BIOT_LIBS ${BIOT_LIBS} -lz -lssl -lcrypto -lpthread -ldl -lrt)

message(STATUS "use libs: ${BIOT_LIBS}")

# 头文件目录
set(INCDIRS . include src include/oatpp-1.3.0/oatpp)
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

# 源码目录
set(BIOT_SRCDIRS src/ src/basic)
set(BIOT_SRCDIRS ${BIOT_SRCDIRS} src/basic/base)
set(BIOT_SRCDIRS ${BIOT_SRCDIRS} src/basic/defs)
set(BIOT_SRCDIRS ${BIOT_SRCDIRS} src/basic/log)
set(BIOT_SRCDIRS ${BIOT_SRCDIRS} src/boot)
set(BIOT_SRCDIRS ${BIOT_SRCDIRS} src/config)
set(BIOT_SRCDIRS ${BIOT_SRCDIRS} src/config/capa)
set(BIOT_SRCDIRS ${BIOT_SRCDIRS} src/config/capa/common)
set(BIOT_SRCDIRS ${BIOT_SRCDIRS} src/config/capa/product)
set(BIOT_SRCDIRS ${BIOT_SRCDIRS} src/config/param)
set(BIOT_SRCDIRS ${BIOT_SRCDIRS} src/config/param/param_pb)

# 查找源码
list_source_directories(BIOT_SRCS ${BIOT_SRCDIRS})

# 编译目标
add_executable(${TARGET} ${BIOT_SRCS})

# 链接库
target_link_libraries(${TARGET} ${BIOT_LIBS})

# 替换__FILE__为相对路径
redefine_file_macro(${TARGET})