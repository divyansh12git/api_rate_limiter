#pragma once

#include <unordered_map>
#include <string>
#include "limiter.hpp"

class TokenBucketLimiter : public RateLimiter {
    struct Bucket {
        double tokens;
        long long last_checked;
    };

    int max_tokens;
    double refill_rate; // tokens per second
    std::unordered_map<std::string, Bucket> buckets;

public:
    TokenBucketLimiter(int max_tokens, double refill_rate);
    bool allowRequest(const std::string& user_id) override;
};
