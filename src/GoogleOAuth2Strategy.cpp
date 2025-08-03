#include "WAY/GoogleOAuth2Strategy.hpp"
#include "httplib.h"
#include "nlohmann/json.hpp"

namespace WAY {
    GoogleOAuth2Strategy::GoogleOAuth2Strategy(const std::string& client_id, const std::string& client_secret, const std::string& redirect_uri)
        : client_id(client_id), client_secret(client_secret), redirect_uri(redirect_uri) {}

    bool GoogleOAuth2Strategy::authenticate(const std::map<std::string, std::string>& credentials) {
        auto code_it = credentials.find("code");
        if (code_it == credentials.end()) {
            return false;
        }

        httplib::Client cli("https://oauth2.googleapis.com");

        httplib::Params params;
        params.emplace("client_id", client_id);
        params.emplace("client_secret", client_secret);
        params.emplace("code", code_it->second);
        params.emplace("redirect_uri", redirect_uri);
        params.emplace("grant_type", "authorization_code");

        auto res = cli.Post("/token", params);

        if (res && res->status == 200) {
            nlohmann::json response = nlohmann::json::parse(res->body);
            std::string access_token = response["access_token"];

            httplib::Client user_info_cli("https://www.googleapis.com");
            httplib::Headers headers = {
                {"Authorization", "Bearer " + access_token}
            };

            auto user_info_res = user_info_cli.Get("/oauth2/v2/userinfo", headers);

            return user_info_res && user_info_res->status == 200;
        }

        return false;
    }

    std::string GoogleOAuth2Strategy::getAuthorizationUrl() {
        return "https://accounts.google.com/o/oauth2/v2/auth?"
               "client_id=" + client_id +
               "&redirect_uri=" + redirect_uri +
               "&response_type=code&scope=openid%20profile%20email";
    }
}
