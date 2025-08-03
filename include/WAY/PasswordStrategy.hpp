#pragma once

#include "WAY/AuthenticationStrategy.hpp"
#include "WAY/IDatabase.hpp"
#include <string>

namespace WAY {
    class PasswordStrategy : public IAuthenticationStrategy {
    public:
        explicit PasswordStrategy(IDatabase& db);
        bool authenticate(const std::map<std::string, std::string>& credentials) override;

    private:
        IDatabase& db;
    };
}