/**
 * MIT License
 * 
 * Copyright © 2021 <wotsen>.
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software
 * and associated documentation files (the “Software”), to deal in the Software without
 * restriction, including without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the
 * 
 * The above copyright notice and this permission notice shall be included in all copies or
 * substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
 * BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 * 
 * @file module.cpp
 * @brief 
 * @author wotsen (astralrovers@outlook.com)
 * @version 1.0.0
 * @date 2021-08-22
 * 
 * @copyright MIT License
 * 
 */
#include "module.h"
#include "config/default_parameter.h"

namespace biot {

/*---------------------system---------------------*/
extern parameter_config_t def_system_param;
/*---------------------hardware-------------------*/
extern parameter_config_t def_hardware_param;
/*---------------------database-------------------*/
extern parameter_config_t def_database_param;
/*---------------------storage--------------------*/
extern parameter_config_t def_storage_param;
/*---------------------network--------------------*/
extern parameter_config_t def_network_param;
/*---------------------application----------------*/
extern parameter_config_t def_application_param;
/*------------------------------------------------*/

parameter_config_t def_module_param = {
	"module",
	"模块配置",
	param_t_object,
	"NA",
	param_p_read_write,
	R"(
	{
	}
	)",
	param_t_object,
	{
		&def_system_param,
		&def_hardware_param,
		&def_database_param,
		&def_storage_param,
		&def_network_param,
		&def_application_param,
	}
};

} // namespace biot
