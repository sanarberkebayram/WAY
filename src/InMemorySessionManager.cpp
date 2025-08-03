#include "WAY/InMemorySessionManager.hpp"
#include <random>
#include <sstream>
#include <iomanip>

namespace WAY {
    std::string InMemorySessionManager::generateSessionId() {
        static std::random_device rd;
        static std::mt19937 generator(rd());
        static std::uniform_int_distribution<> distribution(0, 15);

        std::stringstream ss;
        for (int i = 0; i < 32; ++i) {
            ss << std::hex << distribution(generator);
        }
        return ss.str();
    }

    std::string InMemorySessionManager::createSession(const std::string& username, const std::map<std::string, std::string>& data) {
        std::lock_guard<std::mutex> lock(sessions_mutex);
        cleanupExpiredSessions();

        std::string session_id = generateSessionId();
        sessions[session_id] = {username, data, std::chrono::steady_clock::now() + std::chrono::hours(1)}; // Session expires in 1 hour
        return session_id;
    }

    std::optional<std::map<std::string, std::string>> InMemorySessionManager::getSession(const std::string& session_id) {
        std::lock_guard<std::mutex> lock(sessions_mutex);
        cleanupExpiredSessions();

        auto it = sessions.find(session_id);
        if (it != sessions.end()) {
            if (it->second.expiry_time > std::chrono::steady_clock::now()) {
                return it->second.data;
            } else {
                sessions.erase(it);
            }
        }
        return std::nullopt;
    }

    void InMemorySessionManager::deleteSession(const std::string& session_id) {
        std::lock_guard<std::mutex> lock(sessions_mutex);
        sessions.erase(session_id);
    }

    void InMemorySessionManager::cleanupExpiredSessions() {
        auto now = std::chrono::steady_clock::now();
        for (auto it = sessions.begin(); it != sessions.end(); ) {
            if (it->second.expiry_time <= now) {
                it = sessions.erase(it);
            } else {
                ++it;
            }
        }
    }
}
