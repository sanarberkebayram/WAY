#include "WAY/server.hpp"
#include "WAY/PasswordStrategy.hpp"
#include "WAY/JwtStrategy.hpp"
#include "WAY/GoogleOAuth2Strategy.hpp"
#include "nlohmann/json.hpp"
#include "bcrypt/BCrypt.hpp"

namespace WAY {
    Server::Server(std::unique_ptr<IDatabase> db_ptr, std::unique_ptr<ISessionManager> session_manager_ptr)
        : db(std::move(db_ptr)), session_manager(std::move(session_manager_ptr)) {
        // Add Password Strategy
        auth_service.addStrategy("password", std::make_unique<PasswordStrategy>(*db));

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
                    // Create a session upon successful authentication
                    std::string username = credentials.at("username"); // Assuming username is always present for password strategy
                    std::string session_id = session_manager->createSession(username, {{"authenticated", "true"}});
                    res.set_content("Authentication successful! Session ID: " + session_id, "text/plain");
                } else {
                    res.set_content("Authentication failed!", "text/plain");
                    res.status = 401;
                }
            } catch (const std::exception& e) {
                res.set_content("Invalid request format!", "text/plain");
                res.status = 400;
            }
        });

        http_server.Post("/register", [this](const httplib::Request& req, httplib::Response& res) {
            try {
                nlohmann::json request_body = nlohmann::json::parse(req.body);
                std::string username = request_body["username"];
                std::string password = request_body["password"];

                std::string hashed_password = BCrypt::generateHash(password);
                User user{0, username, hashed_password};
                db->addUser(user);

                res.set_content("User registered successfully!", "text/plain");
            } catch (const std::exception& e) {
                res.set_content("Invalid request format!", "text/plain");
                res.status = 400;
            }
        });

        http_server.Get("/session", [this](const httplib::Request& req, httplib::Response& res) {
            if (req.has_header("Session-ID")) {
                std::string session_id = req.get_header_value("Session-ID");
                auto session_data = session_manager->getSession(session_id);
                if (session_data) {
                    res.set_content("Session data: " + nlohmann::json(*session_data).dump(), "application/json");
                } else {
                    res.set_content("Session not found or expired!", "text/plain");
                    res.status = 404;
                }
            } else {
                res.set_content("Session-ID header missing!", "text/plain");
                res.status = 400;
            }
        });

        http_server.Delete("/session", [this](const httplib::Request& req, httplib::Response& res) {
            if (req.has_header("Session-ID")) {
                std::string session_id = req.get_header_value("Session-ID");
                session_manager->deleteSession(session_id);
                res.set_content("Session deleted!", "text/plain");
            } else {
                res.set_content("Session-ID header missing!", "text/plain");
                res.status = 400;
            }
        });
    }

    void Server::start(int port) {
        http_server.listen("0.0.0.0", port);
    }
}
