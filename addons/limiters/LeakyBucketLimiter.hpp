#pragma once

#include <unordered_map>
#include <string>
#include "limiter.hpp"

class LeakyBucketLimiter : public RateLimiter {
    struct Bucket {
        double tokens;
        long long last_checked;
    };

    int bucket_capacity;
    double leak_rate; // tokens per second
    std::unordered_map<std::string, Bucket> buckets;

public:
    LeakyBucketLimiter(int capacity, double leak_rate);
    bool allowRequest(const std::string& user_id) override;
};
