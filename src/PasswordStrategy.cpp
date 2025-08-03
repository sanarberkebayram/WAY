#include "WAY/PasswordStrategy.hpp"

namespace WAY {
    PasswordStrategy::PasswordStrategy(const std::vector<User>& users) : users(users) {}

    bool PasswordStrategy::authenticate(const std::map<std::string, std::string>& credentials) {
        auto username_it = credentials.find("username");
        auto password_it = credentials.find("password");

        if (username_it == credentials.end() || password_it == credentials.end()) {
            return false;
        }

        const std::string& username = username_it->second;
        const std::string& password = password_it->second;

        for (const auto& user : users) {
            if (user.username == username && user.password_hash == password) {
                return true;
            }
        }

        return false;
    }
}
