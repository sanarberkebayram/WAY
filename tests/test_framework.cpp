#include "WAY/AuthenticationService.hpp"
#include "WAY/PasswordStrategy.hpp"
#include "WAY/JwtStrategy.hpp"
#include "WAY/GoogleOAuth2Strategy.hpp"
#include "WAY/SQLiteDatabase.hpp"
#include "WAY/DatabaseFactory.hpp"
#include "WAY/InMemorySessionManager.hpp"
#include "WAY/User.hpp"
#include "bcrypt/BCrypt.hpp"
#include <cassert>
#include <vector>
#include <map>
#include <iostream>
#include <fstream>

int main() {
    // Clean up previous test database
    std::remove("test.db");

    std::map<std::string, std::string> db_config;
    db_config["path"] = "test.db";
    auto db = WAY::DatabaseFactory::createDatabase("sqlite", db_config);

    auto session_manager = std::make_unique<WAY::InMemorySessionManager>();

    WAY::AuthenticationService auth_service;

    // Add Password Strategy
    auth_service.addStrategy("password", std::make_unique<WAY::PasswordStrategy>(*db));

    // Add JWT Strategy
    auth_service.addStrategy("jwt", std::make_unique<WAY::JwtStrategy>("secret"));

    // Add Google OAuth2 Strategy
    auth_service.addStrategy("google", std::make_unique<WAY::GoogleOAuth2Strategy>("test_client_id", "test_client_secret", "test_redirect_uri"));

    // Add a user to the database with hashed password
    std::string hashed_password = BCrypt::generateHash("password123");
    WAY::User user{0, "testuser", hashed_password};
    db->addUser(user);

    // Test Password Strategy
    std::map<std::string, std::string> password_credentials = {{"username", "testuser"}, {"password", "password123"}};
    assert(auth_service.authenticate("password", password_credentials));

    // Test failed authentication (wrong password)
    std::map<std::string, std::string> wrong_password_credentials = {{"username", "testuser"}, {"password", "wrongpassword"}};
    assert(!auth_service.authenticate("password", wrong_password_credentials));

    // Test JWT Strategy
    WAY::JwtStrategy jwt_strategy("secret");
    std::string token = jwt_strategy.generateToken("testuser");
    std::map<std::string, std::string> jwt_credentials = {{"token", token}};
    assert(auth_service.authenticate("jwt", jwt_credentials));

    // Test session creation and retrieval
    std::string session_id = session_manager->createSession("testuser", {{"authenticated", "true"}});
    auto retrieved_session = session_manager->getSession(session_id);
    assert(retrieved_session.has_value());
    assert(retrieved_session->at("username") == "testuser");

    // Test session deletion
    session_manager->deleteSession(session_id);
    assert(!session_manager->getSession(session_id).has_value());

    // Test Google OAuth2 Strategy (URL generation)
    WAY::GoogleOAuth2Strategy google_strategy("test_client_id", "test_client_secret", "test_redirect_uri");
    std::string auth_url = google_strategy.getAuthorizationUrl();
    assert(auth_url.find("test_client_id") != std::string::npos);

    std::cout << "All tests passed!" << std::endl;

    return 0;
}
