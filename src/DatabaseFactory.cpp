#include "WAY/DatabaseFactory.hpp"
#include "WAY/SQLiteDatabase.hpp"
#include <stdexcept>

namespace WAY {
    std::unique_ptr<IDatabase> DatabaseFactory::createDatabase(const std::string& type, const std::map<std::string, std::string>& config) {
        if (type == "sqlite") {
            return std::make_unique<SQLiteDatabase>(config.at("path"));
        } else {
            throw std::runtime_error("Unknown database type: " + type);
        }
    }
}
