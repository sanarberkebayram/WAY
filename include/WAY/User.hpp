#pragma once

#include <string>
#include <optional>

namespace WAY {
    struct User {
        int id;
        std::string username;
        std::string password_hash;
        std::optional<std::string> google_id;
    };
}