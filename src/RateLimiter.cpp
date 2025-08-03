#include "WAY/RateLimiter.hpp"

namespace WAY {
    RateLimiter::RateLimiter(int max_requests, std::chrono::seconds window_size)
        : max_requests_(max_requests), window_size_(window_size) {}

    bool RateLimiter::allowRequest(const std::string& ip_address) {
        std::lock_guard<std::mutex> lock(mutex_);
        cleanupExpiredRequests(ip_address);

        auto now = std::chrono::steady_clock::now();
        request_timestamps_[ip_address][now]++;

        int request_count = 0;
        for (const auto& pair : request_timestamps_[ip_address]) {
            request_count += pair.second;
        }

        return request_count <= max_requests_;
    }

    void RateLimiter::cleanupExpiredRequests(const std::string& ip_address) {
        auto now = std::chrono::steady_clock::now();
        auto& timestamps = request_timestamps_[ip_address];

        for (auto it = timestamps.begin(); it != timestamps.end(); ) {
            if (now - it->first > window_size_) {
                it = timestamps.erase(it);
            } else {
                ++it;
            }
        }
    }
}
