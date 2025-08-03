#pragma once

#include "WAY/ISessionManager.hpp"
#include <string>
#include <map>
#include <chrono>
#include <mutex>

namespace WAY {
    class InMemorySessionManager : public ISessionManager {
    public:
        std::string createSession(const std::string& username, const std::map<std::string, std::string>& data) override;
        std::optional<std::map<std::string, std::string>> getSession(const std::string& session_id) override;
        void deleteSession(const std::string& session_id) override;

    private:
        struct SessionData {
            std::string username;
            std::map<std::string, std::string> data;
            std::chrono::steady_clock::time_point expiry_time;
        };

        std::map<std::string, SessionData> sessions;
        std::mutex sessions_mutex;

        std::string generateSessionId();
        void cleanupExpiredSessions();
    };
}
