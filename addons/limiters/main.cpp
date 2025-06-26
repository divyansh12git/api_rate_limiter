#include <iostream>
#include "FixedWindowLimiter.hpp"
#include "SlidingLogLimiter.hpp"
#include "TokenBucketLimiter.hpp"
#include "LeakyBucketLimiter.hpp"

int main() {
    // Choose one
    // RateLimiter* limiter = new FixedWindowLimiter(5, 10);
    // RateLimiter* limiter = new SlidingLogLimiter(5, 10);
    // RateLimiter* limiter = new TokenBucketLimiter(5, 1.0);
    RateLimiter* limiter = new LeakyBucketLimiter(5, 1.0); // capacity 5, leak 1 token/sec
    std::string user;
    while (true) {
        std::cout << "Enter user ID (or 'exit'): ";
        std::cin >> user;
        if (user == "exit") break;

        if (limiter->allowRequest(user)) {
            std::cout << "User Allowed\n";
        } else {
            std::cout << "Rate Limit Exceeded\n";
        }
    }

    delete limiter;
    return 0;
}
//g++ main.cpp \
    FixedWindowLimiter.cpp \
    SlidingLogLimiter.cpp \
    TokenBucketLimiter.cpp \
    LeakyBucketLimiter.cpp \
    -o limiter_app -std=c++17
