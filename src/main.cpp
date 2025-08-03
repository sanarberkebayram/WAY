#include "WAY/server.hpp"
#include "WAY/DatabaseFactory.hpp"
#include <iostream>
#include <map>

int main() {
    std::map<std::string, std::string> db_config;
    db_config["path"] = "way.db";
    auto db = WAY::DatabaseFactory::createDatabase("sqlite", db_config);

    WAY::Server server(std::move(db));
    std::cout << "Starting WAY server on port 8080..." << std::endl;
    try {
        server.start(8080);
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}
