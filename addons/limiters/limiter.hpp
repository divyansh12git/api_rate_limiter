#pragma once

#include <string>

class RateLimiter {
public:
    virtual bool allowRequest(const std::string& user_id) = 0;
    virtual ~RateLimiter() = default;
};
