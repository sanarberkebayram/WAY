#pragma once

#include <string>

namespace WAY {
    struct User {
        int id;
        std::string username;
        std::string password_hash;
    };
}
