#pragma once

#include <string>
#include <chrono>
#include <map>
#include <mutex>

namespace WAY {
    class RateLimiter {
    public:
        RateLimiter(int max_requests, std::chrono::seconds window_size);
        bool allowRequest(const std::string& ip_address);

    private:
        int max_requests_;
        std::chrono::seconds window_size_;
        std::map<std::string, std::map<std::chrono::steady_clock::time_point, int>> request_timestamps_;
        std::mutex mutex_;

        void cleanupExpiredRequests(const std::string& ip_address);
    };
}
