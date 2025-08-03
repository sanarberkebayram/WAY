#pragma once

#include "WAY/AuthenticationStrategy.hpp"
#include <string>

namespace WAY {
    class GoogleOAuth2Strategy : public IAuthenticationStrategy {
    public:
        GoogleOAuth2Strategy(const std::string& client_id, const std::string& client_secret, const std::string& redirect_uri);
        bool authenticate(const std::map<std::string, std::string>& credentials) override;
        std::string getAuthorizationUrl();

    private:
        std::string client_id;
        std::string client_secret;
        std::string redirect_uri;
    };
}
