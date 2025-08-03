#pragma once

#include <string>
#include <optional>
#include <map>

namespace WAY {
    class ISessionManager {
    public:
        virtual ~ISessionManager() = default;
        virtual std::string createSession(const std::string& username, const std::map<std::string, std::string>& data) = 0;
        virtual std::optional<std::map<std::string, std::string>> getSession(const std::string& session_id) = 0;
        virtual void deleteSession(const std::string& session_id) = 0;
    };
}
