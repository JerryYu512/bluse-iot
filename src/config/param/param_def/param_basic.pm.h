#pragma once

#include <vector>
#include <string>
#include <stdint.h>
#include <iostream>
#include "param_basic.pm.h"
#include "enums/e_basic.pm.h"

namespace biot { 

typedef struct BiotAppUsers_s BiotAppUsers;
typedef struct BiotAppBasicParam_s BiotAppBasicParam;
typedef struct BiotAppAccessUser_s BiotAppAccessUser;

// 设备访问用户
struct BiotAppAccessUser_s {
	std::string name;                                               ///< 用户名
	std::string passwd;                                             ///< 密码
	uint64_t expired;                                               ///< 有效期
	std::string permission;                                         ///< 权限
	bool allowlist;                                                 ///< 白名单
	std::string email;                                              ///< 邮箱
	std::string phone;                                              ///< 电话
	std::string github;                                             ///< gihub账户
	BiotAppAccessUser_s() {
		name = "";
		passwd = "";
		expired = 0;
		permission = "";
		allowlist = false;
		email = "";
		phone = "";
		github = "";
	}
};

// 用户列表
struct BiotAppUsers_s {
	std::vector<BiotAppAccessUser> access_users;                    ///< 外部接入访问的用户
	BiotAppUsers_s() {
	}
};

// 基础功能配置
struct BiotAppBasicParam_s {
	EBiotAppMode appmode;                                           ///< 运行模式
	BiotAppUsers user;                                              ///< 用户
	BiotAppBasicParam_s() {
	}
};


}
