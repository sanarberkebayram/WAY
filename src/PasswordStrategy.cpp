#include "WAY/PasswordStrategy.hpp"

namespace WAY {
    PasswordStrategy::PasswordStrategy(IDatabase& db) : db(db) {}

    bool PasswordStrategy::authenticate(const std::map<std::string, std::string>& credentials) {
        auto username_it = credentials.find("username");
        auto password_it = credentials.find("password");

        if (username_it == credentials.end() || password_it == credentials.end()) {
            return false;
        }

        const std::string& username = username_it->second;
        const std::string& password = password_it->second;

        auto user = db.getUserByUsername(username);
        if (user && user->password_hash == password) {
            return true;
        }

        return false;
    }
}
