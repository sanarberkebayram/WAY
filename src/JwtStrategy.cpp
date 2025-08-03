#include "WAY/JwtStrategy.hpp"
#include "jwt-cpp/jwt.h"

namespace WAY {
    JwtStrategy::JwtStrategy(const std::string& secret) : secret(secret) {}

    bool JwtStrategy::authenticate(const std::map<std::string, std::string>& credentials) {
        auto token_it = credentials.find("token");
        if (token_it == credentials.end()) {
            return false;
        }

        const std::string& token = token_it->second;

        try {
            auto decoded = jwt::decode(token);
            auto verifier = jwt::verify()
                .allow_algorithm(jwt::algorithm::hs256{secret})
                .with_issuer("WAY");

            verifier.verify(decoded);
            return true;
        } catch (const std::exception& e) {
            return false;
        }
    }

    std::string JwtStrategy::generateToken(const std::string& username) {
        auto token = jwt::create()
            .set_issuer("WAY")
            .set_type("JWS")
            .set_payload_claim("username", jwt::claim(username))
            .sign(jwt::algorithm::hs256{secret});

        return token;
    }
}
