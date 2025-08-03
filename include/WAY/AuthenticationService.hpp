#pragma once

#include "WAY/AuthenticationStrategy.hpp"
#include <map>
#include <string>
#include <memory>

namespace WAY {
    class AuthenticationService {
    public:
        void addStrategy(const std::string& name, std::unique_ptr<IAuthenticationStrategy> strategy);
        bool authenticate(const std::string& strategy_name, const std::map<std::string, std::string>& credentials);

    private:
        std::map<std::string, std::unique_ptr<IAuthenticationStrategy>> strategies;
    };
}
