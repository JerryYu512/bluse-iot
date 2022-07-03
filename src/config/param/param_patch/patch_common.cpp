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
 * @file patch_common.cpp
 * @brief 
 * @author Jerry.Yu (jerry.yu512outlook.com)
 * @version 1.0.0
 * @date 2022-05-16
 * 
 * @copyright MIT License
 * 
 */
#include "biot_configure.h"
#include "config/configure.h"
#include "config/param/param.h"
#include "module/network/netbasic/netport_set.h"

namespace biot {

int patch_common(void) {
	auto header = app_param_header();
	auto param = app_param();

	param.exec_uuid = BIOT_UUID;
	param.modules.network.web.http_port = BIOT_NET_PORT_START + 80;
	put_netport(param.modules.network.web.http_port, "webApp http port");
	param.modules.network.web.https_port = BIOT_NET_PORT_START + 443;
	put_netport(param.modules.network.web.https_port, "webApp https port");
	param.modules.network.web.root = BIOT_WEBAPP_ROOT_PATH;
	param.modules.network.web.connect_max = 1024;

	return 0;
}

} // namespace biot
