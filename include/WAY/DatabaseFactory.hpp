#pragma once

#include "WAY/IDatabase.hpp"
#include <string>
#include <map>
#include <memory>

namespace WAY {
    class DatabaseFactory {
    public:
        static std::unique_ptr<IDatabase> createDatabase(const std::string& type, const std::map<std::string, std::string>& config);
    };
}
