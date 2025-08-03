#include "WAY/server.hpp"
#include <iostream>

int main() {
    WAY::Server server;
    std::cout << "Starting WAY server on port 8080..." << std::endl;
    try {
        server.start(8080);
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}