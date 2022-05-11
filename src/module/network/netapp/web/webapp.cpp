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
 * @file webapp.cpp
 * @brief
 * @author Jerry.Yu (jerry.yu512outlook.com)
 * @version 1.0.0
 * @date 2022-05-08
 *
 * @copyright MIT License
 *
 */
#include <iostream>
#include "basic/defs/func_module.h"
#include "oatpp/network/Server.hpp"
#include "compoent/compoent.hpp"
#include "controller/bapi_root.hpp"
#include "controller/bapi_midware_cntrl.hpp"

namespace biot {

void run() {
    /* Register Components in scope of run() method */
    AppComponent components("0.0.0.0", 8000);

    /* Get router component */
    OATPP_COMPONENT(std::shared_ptr<oatpp::web::server::HttpRouter>, router);

    router->addController(std::make_shared<AuthController>());
    /* Create RootController and add all of its endpoints to router */
    router->addController(std::make_shared<RootController>());

    /* Get connection handler component */
    OATPP_COMPONENT(std::shared_ptr<oatpp::network::ConnectionHandler>, connectionHandler);

    /* Get connection provider component */
    OATPP_COMPONENT(std::shared_ptr<oatpp::network::ServerConnectionProvider>, connectionProvider);

    /* Create server which takes provided TCP connections and passes them to HTTP connection handler
     */
    oatpp::network::Server server(connectionProvider, connectionHandler);

    /* Print info about server port */
    OATPP_LOGI("BiotWebApp", "Server running on port %s", connectionProvider->getProperty("port").getData());

    /* Run server */
    server.run();
}

int webapp_state(void) {
    return FUNC_MODULE_START_OK;
}

int webapp_start(void) {
    oatpp::base::Environment::init();

    run();

    /* Print how much objects were created during app running, and what have left-probably leaked */
    /* Disable object counting for release builds using '-D OATPP_DISABLE_ENV_OBJECT_COUNTERS' flag
     * for better performance */
    std::cout << "\nEnvironment:\n";
    std::cout << "objectsCount = " << oatpp::base::Environment::getObjectsCount() << "\n";
    std::cout << "objectsCreated = " << oatpp::base::Environment::getObjectsCreated() << "\n\n";

    oatpp::base::Environment::destroy();

	return FUNC_MODULE_START_OK;
}

}  // namespace biot
