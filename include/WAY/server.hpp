#pragma once

#include "WAY/AuthenticationService.hpp"
#include "WAY/IDatabase.hpp"
#include "WAY/ISessionManager.hpp"
#include "httplib.h"
#include <memory>

namespace WAY {
    class Server {
    public:
        explicit Server(std::unique_ptr<IDatabase> db, std::unique_ptr<ISessionManager> session_manager);
        void start(int port);

    private:
        httplib::Server http_server;
        AuthenticationService auth_service;
        std::unique_ptr<IDatabase> db;
        std::unique_ptr<ISessionManager> session_manager;
    };
}