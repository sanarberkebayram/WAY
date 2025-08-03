#include "WAY/server.hpp"
#include "WAY/DatabaseFactory.hpp"
#include "WAY/InMemorySessionManager.hpp"
#include <iostream>
#include <map>

int main() {
    std::map<std::string, std::string> db_config;
    db_config["path"] = "way.db";
    auto db = WAY::DatabaseFactory::createDatabase("sqlite", db_config);

    auto session_manager = std::make_unique<WAY::InMemorySessionManager>();

    WAY::Server server(std::move(db), std::move(session_manager));
    std::cout << "Starting WAY server on port 8080..." << std::endl;
    try {
        server.start(8080);
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}
