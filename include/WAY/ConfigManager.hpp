#pragma once

#include <string>
#include <map>
#include "nlohmann/json.hpp"

namespace WAY {
    class ConfigManager {
    public:
        ConfigManager();
        void loadConfig(const std::string& file_path);
        std::string getString(const std::string& key, const std::string& default_value = "") const;
        int getInt(const std::string& key, int default_value = 0) const;

    private:
        nlohmann::json config_data;
        void loadEnvironmentVariables();
    };
}