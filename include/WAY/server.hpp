#pragma once

#include "WAY/AuthenticationService.hpp"
#include "httplib.h"

namespace WAY {
    class Server {
    public:
        Server();
        void start(int port);

    private:
        httplib::Server http_server;
        AuthenticationService auth_service;
    };
}