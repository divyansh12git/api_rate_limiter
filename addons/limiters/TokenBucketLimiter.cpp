#include "TokenBucketLimiter.hpp"
#include <chrono>
#include <algorithm> // for std::min
#include<iostream>
using namespace std;
TokenBucketLimiter::TokenBucketLimiter(int max_tokens, double refill_rate)
    : max_tokens(max_tokens), refill_rate(refill_rate) {}

bool TokenBucketLimiter::allowRequest(const std::string& user_id) {
    long long now = std::chrono::duration_cast<std::chrono::milliseconds>(
                        std::chrono::system_clock::now().time_since_epoch())
                        .count();

    auto& bucket = buckets[user_id];

    if (bucket.last_checked == 0 && bucket.tokens == 0) {
        bucket = { (double)max_tokens - 1, now }; 
        return true;
    }

    double elapsed = (now - bucket.last_checked) / 1000.0; // seconds
    bucket.tokens = std::min((double)max_tokens, bucket.tokens + elapsed * refill_rate);
    bucket.last_checked = now;
    // cout<<max_tokens<<" "<<bucket.tokens<<" "<<elapsed <<" "<< refill_rate<<" "<<elapsed * refill_rate<<endl;
    if (bucket.tokens >= 1.0) {
        bucket.tokens -= 1.0;
        return true;
    }

    return false;
}


// suppose this like a bucket filling at smoe refill_rate
// custum struct Bucket-->last and tokens 
// now-last time give what is elapsed time now bucket token+elap*refill_rate gives the exact token now store it in bucket
// give response accordingly  
