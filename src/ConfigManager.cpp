#include "WAY/ConfigManager.hpp"
#include <fstream>
#include <iostream>

namespace WAY {
    ConfigManager::ConfigManager() {
        loadEnvironmentVariables();
    }

    void ConfigManager::loadConfig(const std::string& file_path) {
        std::ifstream file(file_path);
        if (file.is_open()) {
            try {
                nlohmann::json file_config = nlohmann::json::parse(file);
                for (auto it = file_config.begin(); it != file_config.end(); ++it) {
                    config_data[it.key()] = it.value();
                }
            } catch (const nlohmann::json::parse_error& e) {
                std::cerr << "Error parsing config file: " << e.what() << std::endl;
            }
        } else {
            std::cerr << "Warning: Config file not found: " << file_path << std::endl;
        }
        loadEnvironmentVariables(); // Environment variables take precedence
    }

    std::string ConfigManager::getString(const std::string& key, const std::string& default_value) const {
        if (config_data.contains(key) && config_data[key].is_string()) {
            return config_data[key].get<std::string>();
        }
        return default_value;
    }

    int ConfigManager::getInt(const std::string& key, int default_value) const {
        if (config_data.contains(key) && config_data[key].is_number_integer()) {
            return config_data[key].get<int>();
        }
        return default_value;
    }

    void ConfigManager::loadEnvironmentVariables() {
        // Example: Load WAY_PORT, WAY_DB_TYPE, WAY_DB_PATH
        const char* port_env = std::getenv("WAY_PORT");
        if (port_env) {
            config_data["port"] = std::stoi(port_env);
        }

        const char* db_type_env = std::getenv("WAY_DB_TYPE");
        if (db_type_env) {
            config_data["db_type"] = db_type_env;
        }

        const char* db_path_env = std::getenv("WAY_DB_PATH");
        if (db_path_env) {
            config_data["db_path"] = db_path_env;
        }
    }
}