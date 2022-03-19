# version
RELEASE_VERSION = 1.0.0
PLAT_NAME = $(shell uname -m)
OS_NAME = $(shell uname)

ifneq ($(VERSION),)
	RELEASE_VERSION = $(VERSION)
endif

MAKE_INSTALL_DIR = install

# 调试模式使能
DEBUG = n

# 使用的加密套件
# WITH_OPENSSL
# WITH_MBEDTLS
# MBEDTLS_SSL_CACHE_C

# make path
export MAKE := "/usr/bin/make"

# make flag
MAKEFLAG := -s --no-print-directory

# compile marcro
export CC := $(TOOL_PREFIX)gcc
export CXX := $(TOOL_PREFIX)g++
AR := $(TOOL_PREFIX)ar rcs
SHAREDFLG := -shared
# 编译时间
COMPILE_TIME := $(shell date +"%A %Y-%m-%d %H:%M:%S %z")
BUILD_VERSION := $(shell date +"%Y%m%d%H%M")
ifeq ($(shell which uuid), )
APP_UUID := 00000000-0000-0000-0000-000000000000
else
APP_UUID := $(shell uuid)
endif

# compile flags
INC := -I/usr/include -I/usr/local/include -I$(ROOT_DIR)/include -I$(ROOT_DIR)/src -I$(ROOT_DIR) -Ibuild

LIBS_PATH := -L$(ROOT_DIR)/lib -L/usr/local/lib -L/usr/lib

# ifeq ($(OS_NAME), Darwin)
# INC += -I/usr/local/opt/openssl@1.1/include
# LIBS_PATH += -L/usr/local/opt/openssl@1.1/lib
# endif

#-levent 
# ST_LIBS = -lgflags -lprotobuf -lleveldb -lsnappy \
# 		  -lprotoc -lglog -lbrpc \
# 		  -lmongocxx-static -lbsoncxx-static -lmongoc-static-1.0 -lbson-static-1.0 \
# 		  -lssl -lcrypto -lz

ST_LIBS_UT = -lgtest

ST_LIBS = -lbrsdk -lhw-iot-dev-access -lspdlog -lpaho-mqtt3a -lpaho-mqtt3as -lpaho-mqtt3c -lpaho-mqtt3cs
SO_LIBS = -lz -lssl -lcrypto -lpthread -ldl -lrt # -lresolv

DMARCROS := -DLANGUAGE_ZH -DWITH_OPENSSL -DWITH_ZLIB -DSOFT_VERSION=\"$(RELEASE_VERSION)\" \
			-DAPP_COMPILE_TIME=\""$(COMPILE_TIME)"\" -DBUILD_VERSION="\"$(BUILD_VERSION)"\" \
			-DAPP_UUID=\""$(APP_UUID)"\" \
			-DJM_CIRCULAR_BUFFER_CXX_14

# 调试模式
ifeq ($(DEBUG), n)
DMARCROS += -DNDEBUG
CCFLAG = -O3
MODE = release
else
DMARCROS += -DDEBUG
CCFLAG = -g -rdynamic
MODE = debug
endif

DMARCROS += -D__const__= -pipe -W -Wall -Wno-unused-parameter \
			-fPIC -fno-omit-frame-pointer -Wno-implicit-fallthrough \
			-fstack-protector-all -Wno-deprecated-declarations \
			-Wno-class-memaccess -Wno-unknown-warning-option \
			-Wno-tautological-constant-out-of-range-compare \
			-Wno-unused-result -Wno-maybe-uninitialized

# -ggdb
CCFLAG += -c $(INC) -Wall -std=c++14 $(DMARCROS)
OBJCCFLAG := $(CCFLAG)
