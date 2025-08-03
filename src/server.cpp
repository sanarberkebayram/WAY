#include "WAY/server.hpp"
#include "WAY/PasswordStrategy.hpp"
#include "WAY/JwtStrategy.hpp"
#include "WAY/GoogleOAuth2Strategy.hpp"
#include "nlohmann/json.hpp"

namespace WAY {
    Server::Server() {
        // Add Password Strategy
        std::vector<User> users = {{"testuser", "password123"}};
        auth_service.addStrategy("password", std::make_unique<PasswordStrategy>(users));

        // Add JWT Strategy
        auth_service.addStrategy("jwt", std::make_unique<JwtStrategy>("secret"));

        // Add Google OAuth2 Strategy
        auth_service.addStrategy("google", std::make_unique<GoogleOAuth2Strategy>("YOUR_CLIENT_ID", "YOUR_CLIENT_SECRET", "YOUR_REDIRECT_URI"));

        http_server.Post("/authenticate", [this](const httplib::Request& req, httplib::Response& res) {
            try {
                nlohmann::json request_body = nlohmann::json::parse(req.body);
                std::string strategy = request_body["strategy"];
                std::map<std::string, std::string> credentials = request_body["credentials"].get<std::map<std::string, std::string>>();

                if (auth_service.authenticate(strategy, credentials)) {
                    res.set_content("Authentication successful!", "text/plain");
                } else {
                    res.set_content("Authentication failed!", "text/plain");
                    res.status = 401;
                }
            } catch (const std::exception& e) {
                res.set_content("Invalid request format!", "text/plain");
                res.status = 400;
            }
        });
    }

    void Server::start(int port) {
        http_server.listen("0.0.0.0", port);
    }
}