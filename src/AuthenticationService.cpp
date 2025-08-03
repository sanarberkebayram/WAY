#include "WAY/AuthenticationService.hpp"

namespace WAY {
    void AuthenticationService::addStrategy(const std::string& name, std::unique_ptr<IAuthenticationStrategy> strategy) {
        strategies[name] = std::move(strategy);
    }

    bool AuthenticationService::authenticate(const std::string& strategy_name, const std::map<std::string, std::string>& credentials) {
        auto it = strategies.find(strategy_name);
        if (it != strategies.end()) {
            return it->second->authenticate(credentials);
        }
        return false;
    }
}
