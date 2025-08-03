#pragma once

#include "User.hpp"
#include <string>
#include <optional>
#include <vector>

namespace WAY {
    class IDatabase {
    public:
        virtual ~IDatabase() = default;
        virtual std::optional<User> getUserByUsername(const std::string& username) = 0;
        virtual void addUser(const User& user) = 0;
    };
}
