#!/bin/bash

ROOT_DIR=$(pwd)
ALL_MODULES=("brsdk" "mqtt" "spdlog" "cjson" "iot-access" "simdjson" "oatpp" "hedley")
SUBMODULE_NAME=""
BUILD_ALL="false"

while getopts "n:a:" arg #选项后面的冒号表示该选项需要参数
do
    case $arg in
        n)
            echo "build submodule $OPTARG" #参数存在$OPTARG中
			SUBMODULE_NAME=${OPTARG}
            ;;
        a)
            echo "build all submodule"
			BUILD_ALL=${OPTARG}
            ;;
        ?)  #当有不认识的选项的时候arg为?
            echo "unkonw argument"
            exit 1
        ;;
    esac
done

build_brsdk()
{
	cd brsdk
	make ENABLE_STATIC_LIB=y MAKE_INSTALL_DIR=${ROOT_DIR}
	make install ENABLE_STATIC_LIB=y MAKE_INSTALL_DIR=${ROOT_DIR}
	make clean
	cd ..
	echo "build ######################### brsdk finish ##################################"
}

build_mqtt()
{
	cd paho.mqtt.c
	rm -rf build
	mkdir -p build
	cd build
	cmake .. -DPAHO_BUILD_SHARED=FALSE -DPAHO_BUILD_STATIC=TRUE -DPAHO_BUILD_SAMPLES=TRUE -DPAHO_WITH_SSL=TRUE -DCMAKE_INSTALL_PREFIX=${ROOT_DIR}
	make
	make install
	make clean
	cd ..
	rm -rf build
	cd ..
}

build_spdlog()
{
	cd spdlog
	rm -rf build
	mkdir -p build
	cd build
	cmake .. -DCMAKE_INSTALL_PREFIX=${ROOT_DIR}
	make
	make install
	make clean
	cd ..
	rm -rf build
	cd ..
}

build_cjson()
{
	cd cJSON
	rm -rf build
	mkdir build
	cd build
	cmake .. -DENABLE_CJSON_UTILS=On -DENABLE_CJSON_TEST=Off -DBUILD_SHARED_LIBS=Off -DBUILD_SHARED_AND_STATIC_LIBS=On -DCMAKE_INSTALL_PREFIX=${ROOT_DIR}
	make
	make install
	cd ..
	rm -rf build
	cd ..
	echo "build ######################### brsdk finish ##################################"
}

build_iot_access()
{
	cd huaweicloud-iot-device-sdk-c
	cp -f ../hw_iot_dev_sdk.mk ./
	make -f hw_iot_dev_sdk.mk MAKE_INSTALL_DIR=${ROOT_DIR}
	make -f hw_iot_dev_sdk.mk install MAKE_INSTALL_DIR=${ROOT_DIR}
	make -f hw_iot_dev_sdk.mk clean MAKE_INSTALL_DIR=${ROOT_DIR}
	rm -f hw_iot_dev_sdk.mk
	cd ..
}

build_oatpp()
{
	cd oatpp
	rm -rf build
	mkdir -p build
	cd build
	cmake .. -DCMAKE_INSTALL_PREFIX=${ROOT_DIR}
	make
	make install
	make clean
	cd ..
	rm -rf build
	cd ..
}

build_simdjson()
{
	cd simdjson
	rm -rf build
	mkdir -p build
	cd build
	cmake .. -DCMAKE_INSTALL_PREFIX=${ROOT_DIR}
	make
	make install
	make clean
	cd ..
	rm -rf build
	cd ..
}

build_one()
{
	echo "######################### build $1 begin ###################################"
	if [ "$1" == "brsdk" ]; then
		build_brsdk
	elif [ "$1" == "mqtt" ]; then
		build_mqtt
	elif [ "$1" == "spdlog" ]; then
		build_spdlog
	elif [ "$1" == "cjson" ]; then
		build_cjson
	elif [ "$1" == "iot-access" ]; then
		build_iot_access
	elif [ "$1" == "simdjson" ]; then
		build_simdjson
	elif [ "$1" == "oatpp" ]; then
		build_oatpp
	elif [ "$1" == "oatpp" ]; then
		mkdir -p ${ROOT_DIR}/include/hedley
		cp hedley/hedley.h ${ROOT_DIR}/include/hedley/
	else
		echo "######################### build $1 failed ###################################"
		return -1
	fi
	echo "######################### build $1 finish ###################################"
	return 0
}

main()
{
	cd thirdparty

	if [ ${BUILD_ALL} == "true" ]; then
		for item in "${ALL_MODULES[@]}"; do
			build_one ${item}
		done
	else
		build_one ${SUBMODULE_NAME}
	fi
}

main
