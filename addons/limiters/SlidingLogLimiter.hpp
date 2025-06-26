#pragma once

#include <unordered_map>
#include <deque>
#include <string>
#include "limiter.hpp"

class SlidingLogLimiter : public RateLimiter {
    int max_requests;
    int window_size; // in seconds
    std::unordered_map<std::string, std::deque<long long>> user_logs;


    public:
        SlidingLogLimiter(int limit, int window);
        bool allowRequest(const std::string& user_id) override;
};
