#include "WAY/AuthenticationService.hpp"
#include "WAY/PasswordStrategy.hpp"
#include "WAY/JwtStrategy.hpp"
#include "WAY/GoogleOAuth2Strategy.hpp"
#include "WAY/User.hpp"
#include <cassert>
#include <vector>
#include <map>
#include <iostream>

int main() {
    WAY::AuthenticationService auth_service;

    // Add Password Strategy
    std::vector<WAY::User> users = {{"testuser", "password123"}};
    auth_service.addStrategy("password", std::make_unique<WAY::PasswordStrategy>(users));

    // Add JWT Strategy
    auth_service.addStrategy("jwt", std::make_unique<WAY::JwtStrategy>("secret"));

    // Add Google OAuth2 Strategy
    auth_service.addStrategy("google", std::make_unique<WAY::GoogleOAuth2Strategy>("test_client_id", "test_client_secret", "test_redirect_uri"));

    // Test Password Strategy
    std::map<std::string, std::string> password_credentials = {{"username", "testuser"}, {"password", "password123"}};
    assert(auth_service.authenticate("password", password_credentials));

    // Test JWT Strategy
    WAY::JwtStrategy jwt_strategy("secret");
    std::string token = jwt_strategy.generateToken("testuser");
    std::map<std::string, std::string> jwt_credentials = {{"token", token}};
    assert(auth_service.authenticate("jwt", jwt_credentials));

    // Test Google OAuth2 Strategy (URL generation)
    WAY::GoogleOAuth2Strategy google_strategy("test_client_id", "test_client_secret", "test_redirect_uri");
    std::string auth_url = google_strategy.getAuthorizationUrl();
    assert(auth_url.find("test_client_id") != std::string::npos);

    std::cout << "All tests passed!" << std::endl;

    return 0;
}
