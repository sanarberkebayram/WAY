#pragma once

#include "WAY/AuthenticationStrategy.hpp"
#include "WAY/User.hpp"
#include <vector>

namespace WAY {
    class PasswordStrategy : public IAuthenticationStrategy {
    public:
        explicit PasswordStrategy(const std::vector<User>& users);
        bool authenticate(const std::map<std::string, std::string>& credentials) override;

    private:
        const std::vector<User>& users;
    };
}
