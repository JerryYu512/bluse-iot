#pragma once

#include <vector>
#include <string>
#include <stdint.h>
#include <iostream>
#include "module_network.pm.h"
#include "enums/e_network.pm.h"

namespace biot { 

typedef struct BiotAppWebServiceParam_s BiotAppWebServiceParam;
typedef struct BiotAppRtsp_s BiotAppRtsp;
typedef struct BiotAppOatppApi_s BiotAppOatppApi;
typedef struct BiotAppNetwork_s BiotAppNetwork;
typedef struct BiotAppLanParam_s BiotAppLanParam;
typedef struct BiotAppCmdApi_s BiotAppCmdApi;

// 命令行服务
struct BiotAppCmdApi_s {
	uint32_t port;
	uint32_t ipv4;
	BiotAppModuleProtocol trans;                                    ///< 通信协议
	BiotAppModulePayload body;                                      ///< body内容:json/xml
	BiotAppCmdApi_s() {
		port = 0;
		ipv4 = 0;
		trans = static_cast<BiotAppModuleProtocol>(0);
		body = static_cast<BiotAppModulePayload>(0);
	}
};

// 有线网参数
struct BiotAppLanParam_s {
	NetLanType type;
	NetCfgType cfg_type;
	std::string if_name;
	std::string mac;
	std::string ipv4;
	std::string ipv6;
	std::string submask;
	std::string gateway;
	uint32_t mtu;                                                   ///< mtu值[eg:1500][range:536<==>1500][type:uint32]
	std::string dns;
	float x1;
	double x2;
	bool x3;
	BiotAppLanParam_s() {
		type = static_cast<NetLanType>(0);
		cfg_type = static_cast<NetCfgType>(0);
		if_name = "";
		mac = "";
		ipv4 = "";
		ipv6 = "";
		submask = "";
		gateway = "";
		mtu = 1500;
		dns = "";
		x1 = 0.0;
		x2 = 0.0;
		x3 = false;
	}
};

// oatpp开放api
struct BiotAppOatppApi_s {
	uint32_t port;
	uint32_t ipv4;
	BiotAppModulePayload body;                                      ///< body内容:json/xml
	BiotAppOatppApi_s() {
		port = 0;
		ipv4 = 0;
		body = static_cast<BiotAppModulePayload>(0);
	}
};

// rtsp
struct BiotAppRtsp_s {
	BiotAppRtsp_s() {
	}
};

// web服务参数
struct BiotAppWebServiceParam_s {
	uint32_t http_port;                                             ///< http端口号
	uint32_t https_port;                                            ///< https端口号
	bool http;                                                      ///< 使能http
	bool https;                                                     ///< 使能https
	std::string root;                                               ///< 根路径
	uint32_t connect_max;                                           ///< 最大连接数
	BiotAppWebServiceParam_s() {
		http_port = 0;
		https_port = 0;
		http = false;
		https = false;
		root = "";
		connect_max = 0;
	}
};

struct BiotAppNetwork_s {
	std::vector<BiotAppLanParam> lan;
	BiotAppWebServiceParam web;
	BiotAppOatppApi openapi;
	BiotAppCmdApi cmdapi;
	BiotAppNetwork_s() {
	}
};


}
