#pragma once

#include <unordered_map>
#include <string>
#include "limiter.hpp"

class FixedWindowLimiter : public RateLimiter {
    int max_requests;
    int window_size; // in seconds
    std::unordered_map<std::string, std::pair<int, long long>> user_data;

public:
    FixedWindowLimiter(int limit, int window);
    bool allowRequest(const std::string& user_id) override;
};
