#pragma once

#include "WAY/AuthenticationStrategy.hpp"
#include <string>

namespace WAY {
    class JwtStrategy : public IAuthenticationStrategy {
    public:
        explicit JwtStrategy(const std::string& secret);
        bool authenticate(const std::map<std::string, std::string>& credentials) override;
        std::string generateToken(const std::string& username);

    private:
        std::string secret;
    };
}
