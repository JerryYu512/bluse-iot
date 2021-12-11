# 目标
TARGET := ars-iot
# 单元测试目标
UNIT_TEST_TARGET := $(TARGET)_ut
ROOT_DIR := $(shell pwd)

# 源码路径
SRC_DIR := src
UT_DIR := unittest

# 临时目录
BUILD_DIR := build
DIST_DIR := dist

# 配置
include config.mk

# 源文件
SOURCES := $(shell find $(SRC_DIR) -type f -name *.cpp)
# 单元测试文件
UT_SOURCES := $(shell find $(UT_DIR) -type f -name *.cpp)

# 替换后缀
OBJECTS := $(patsubst $(SRC_DIR)/%, $(BUILD_DIR)/$(SRC_DIR)/%,$(SOURCES:.cpp=.o))
UT_OBJECTS := $(patsubst $(UT_DIR)/%, $(BUILD_DIR)/$(UT_DIR)/%,$(UT_SOURCES:.cpp=.o))

# 临时依赖文件，用于分析每个.o文件依赖的头文件，在依赖的头文件变化时重新编译.o
DEPS := $(OBJECTS:%.o=%.d)
DEPS += $(UT_OBJECTS:%.o=%.d)

default: $(TARGET)

.PHONY: all
all: pack demo ut

$(TARGET): $(OBJECTS)
	@$(CXX) $(OBJECTS) -o build/$@ $(ST_LIBS) $(SO_LIBS) $(LIBS_PATH)
	@echo "\033[35m[---------- build lib success ----------]\033[0m"
	@echo ""

# 示例代码编译
.PHONY: demo
demo: $(TARGET)
	@make -C samples ARS_INC_DIR=$(ROOT_DIR)/include ARS_LIB_DIR=$(ROOT_DIR)/build OUTPUT_DIR=$(ROOT_DIR)/build/samples

# 单元测试
ut: $(TARGET) $(UT_OBJECTS)
	@$(CXX) $(LIBS_PATH) $(UT_OBJECTS) -l$(TARGET) -Lbuild $(ST_LIBS_UT) $(ST_LIBS) $(SO_LIBS) -o build/$(UNIT_TEST_TARGET)
	@echo "\033[35m[---------- build ut success -----------]\033[0m"
	@echo ""

# Doxygen文档
.PHONY: api
api:

.PHONY: install
install:

# 打包
.PHONY: pack
pack: $(TARGET) api
# 	@echo "\033[35m[----------- package start -------------]\033[0m"
# 	@echo "\033[35m[---------- package success ------------]\033[0m"
# 	@echo ""

.PHONY: clean
clean:
	@echo clean
	@rm -rf $(BUILD_DIR)
	@rm -rf $(DIST_DIR)

# dependencies
-include $(DEPS)
$(BUILD_DIR)/%.o: %.c* $(CONFIG_HEADER)
	@echo "\033[32m$(CXX) $<\033[0m"
	@if [ ! -d $(dir $@) ]; then mkdir -p $(dir $@); fi;\
	$(CXX) $(OBJCCFLAG) -MM -MT $@ -MF $(patsubst %.o, %.d, $@) $<; \
	$(CXX) $(OBJCCFLAG) $< -o $@
