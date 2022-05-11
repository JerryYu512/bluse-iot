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
 * @file compoent.hpp
 * @brief
 * @author Jerry.Yu (jerry.yu512outlook.com)
 * @version 1.0.0
 * @date 2022-05-08
 *
 * @copyright MIT License
 *
 */
#pragma once

#include "oatpp/web/server/HttpConnectionHandler.hpp"
#include "oatpp/network/tcp/server/ConnectionProvider.hpp"
#include "oatpp/parser/json/mapping/ObjectMapper.hpp"
#include "oatpp/core/macro/component.hpp"
#include "config/configure.h"

class AuthInterceptor : public oatpp::web::server::interceptor::RequestInterceptor {
private:
    oatpp::web::server::HttpRouterTemplate<bool> authEndpoints;
public:
    AuthInterceptor() {
        // 不用校验账户
        authEndpoints.route("POST", "login", false);
        authEndpoints.route("POST", "auth", false);
        authEndpoints.route("GET", "user", false);
        authEndpoints.route("OPTIONS", "*", false);

        // 其他全部需要校验
        authEndpoints.route("POST", "*", true);
        authEndpoints.route("PUT", "*", true);
        authEndpoints.route("GET", "*", true);
        authEndpoints.route("DELETE", "*", true);
        authEndpoints.route("HEAD", "*", true);
    }

    std::shared_ptr<OutgoingResponse> intercept(const std::shared_ptr<IncomingRequest>& request) override {
        auto r = authEndpoints.getRoute(request->getStartingLine().method, request->getStartingLine().path);
        if (r && r.getEndpoint() == true) {
            // 校验用户登录
            auto header = request->getHeader(oatpp::web::protocol::http::Header::AUTHORIZATION);
            oatpp::web::server::handler::BasicAuthorizationHandler defAuthHandler;
            auto auth = std::static_pointer_cast<oatpp::web::server::handler::DefaultBasicAuthorizationObject>(defAuthHandler.handleAuthorization(header));
            OATPP_LOGD(BIOT_WEBAPP_NAME, "header=\"%s\" -> user=\"%s\" password=\"%s\"", header->c_str(), auth->userId->c_str(), auth->password->c_str());

            // TODO:使用真实的用户名密码
            if (auth->userId == BIOT_WEBAPP_DEFAULT_USER_NAME && auth->password == BIOT_WEBAPP_DEFAULT_USER_PASSWD) {
                return nullptr;
            } else {
                oatpp::web::protocol::http::Headers resHeader;
                oatpp::data::stream::BufferOutputStream stream;
                stream << BIOT_WEBAPP_DEFAULT_AUTH << " " << "realm=\"" << BIOT_WEBAPP_DEFAULT_BASIC_AUTH_REALM << "\"";
                resHeader.put_LockFree(oatpp::web::protocol::http::Header::WWW_AUTHENTICATE, stream.toString());
                throw oatpp::web::protocol::http::HttpError(oatpp::web::protocol::http::Status::CODE_401, "Unauthorized", resHeader);
            }
        }

        return nullptr;
    }
};

class AccessLogInterceptor : public oatpp::web::server::interceptor::RequestInterceptor {
private:
    uint64_t access_cnt;
public:
    std::shared_ptr<OutgoingResponse> intercept(const std::shared_ptr<IncomingRequest>& request) override {
        access_cnt++;
        OATPP_LOGD(BIOT_WEBAPP_NAME, "%s %s %s", request->getStartingLine().method.toString()->c_str(), request->getStartingLine().path.toString()->c_str(), request->getStartingLine().protocol.toString()->c_str());
        return nullptr;
    }
};

class ResponseLogInterceptor : public oatpp::web::server::interceptor::ResponseInterceptor {
private:
    uint64_t response_cnt;
public:
    std::shared_ptr<OutgoingResponse> intercept(const std::shared_ptr<IncomingRequest>& request,
                                                const std::shared_ptr<OutgoingResponse>& response) override {
        response_cnt++;
        OATPP_LOGD(BIOT_WEBAPP_NAME, "%s %s %s", request->getStartingLine().method.toString()->c_str(), request->getStartingLine().path.toString()->c_str(), request->getStartingLine().protocol.toString()->c_str());
        OATPP_LOGD(BIOT_WEBAPP_NAME, "%d %s", response->getStatus().code, response->getStatus().description);
        return response;
    }
};

// TODO:错误过滤
// TODO:接口访问统计

/**
 *  Class which creates and holds Application components and registers components in
 * oatpp::base::Environment Order of components initialization is from top to bottom
 */
class AppComponent {
public:
	AppComponent(const std::string& ip, uint16_t port) : ip_(ip), port_(port) {}
	AppComponent() : ip_("0.0.0.0"), port_(9000) {}
	std::string ip_;
	uint16_t port_;
public:
    /**
     *  Create ConnectionProvider component which listens on the port
     */
    OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::network::ServerConnectionProvider>,
                           serverConnectionProvider)
    ([this] {
        return oatpp::network::tcp::server::ConnectionProvider::createShared(
            {this->ip_, this->port_, oatpp::network::Address::IP_4});
    }());

    /**
     *  Create Router component
     */
    OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::web::server::HttpRouter>, httpRouter)
    ([] { return oatpp::web::server::HttpRouter::createShared(); }());

    /**
     *  Create ConnectionHandler component which uses Router component to route requests
     */
    OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::network::ConnectionHandler>,
                           serverConnectionHandler)
    ([] {
        OATPP_COMPONENT(std::shared_ptr<oatpp::web::server::HttpRouter>, router);  // get Router component

        auto connectionHandler = oatpp::web::server::HttpConnectionHandler::createShared(router);

        // 请求中间间适配器
        connectionHandler->addRequestInterceptor(std::make_shared<AccessLogInterceptor>());
        connectionHandler->addRequestInterceptor(std::make_shared<AuthInterceptor>());

        // 应答中间间适配器
        connectionHandler->addResponseInterceptor(std::make_shared<ResponseLogInterceptor>());

        return connectionHandler;
    }());

    /**
     *  Create ObjectMapper component to serialize/deserialize DTOs in Contoller's API
     */
    OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::data::mapping::ObjectMapper>, apiObjectMapper)
    ([] { return oatpp::parser::json::mapping::ObjectMapper::createShared(); }());
};
