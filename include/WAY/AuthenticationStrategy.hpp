#pragma once

#include <string>
#include <map>

namespace WAY {
    class IAuthenticationStrategy {
    public:
        virtual ~IAuthenticationStrategy() = default;
        virtual bool authenticate(const std::map<std::string, std::string>& credentials) = 0;
    };
}
