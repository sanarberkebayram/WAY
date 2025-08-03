#include <iostream>
#include <string>
#include <map>
#include <cstdlib> // For getenv
#include "WAY/server.hpp"
#include "WAY/DatabaseFactory.hpp"
#include "WAY/InMemorySessionManager.hpp"

// Function to get environment variable or default value
std::string get_env_var(const std::string& var_name, const std::string& default_value) {
    const char* value = std::getenv(var_name.c_str());
    return value ? value : default_value;
}

int main(int argc, char* argv[]) {
    // Parse command line arguments (basic example)
    int port = 8080;
    std::string db_type = "sqlite";
    std::string db_path = "way.db";

    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg == "--port" && i + 1 < argc) {
            port = std::stoi(argv[++i]);
        } else if (arg == "--db-type" && i + 1 < argc) {
            db_type = argv[++i];
        } else if (arg == "--db-path" && i + 1 < argc) {
            db_path = argv[++i];
        } else if (arg == "--help") {
            std::cout << "Usage: " << argv[0] << " [OPTIONS]\n"
                      << "  --port <port>      Set the server port (default: 8080)\n"
                      << "  --db-type <type>   Set the database type (default: sqlite)\n"
                      << "  --db-path <path>   Set the database path (for sqlite, default: way.db)\n"
                      << "  --help             Display this help message\n";
            return 0;
        }
    }

    // Override with environment variables if set
    port = std::stoi(get_env_var("WAY_PORT", std::to_string(port)));
    db_type = get_env_var("WAY_DB_TYPE", db_type);
    db_path = get_env_var("WAY_DB_PATH", db_path);

    std::map<std::string, std::string> db_config;
    if (db_type == "sqlite") {
        db_config["path"] = db_path;
    } else {
        std::cerr << "Error: Unsupported database type via CLI: " << db_type << std::endl;
        return 1;
    }

    auto db = WAY::DatabaseFactory::createDatabase(db_type, db_config);
    auto session_manager = std::make_unique<WAY::InMemorySessionManager>();

    WAY::Server server(std::move(db), std::move(session_manager));
    std::cout << "Starting WAY server on port " << port << "..." << std::endl;
    try {
        server.start(port);
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}
