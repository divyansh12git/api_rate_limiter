#include "LeakyBucketLimiter.hpp"
#include <chrono>
#include <algorithm>
using namespace std;


LeakyBucketLimiter::LeakyBucketLimiter(int capacity, double leak_rate)
    : bucket_capacity(capacity), leak_rate(leak_rate) {}

bool LeakyBucketLimiter::allowRequest(const string& user_id) {
    long long now = chrono::duration_cast<chrono::milliseconds>(
                        chrono::system_clock::now().time_since_epoch())
                        .count();

    auto& bucket = buckets[user_id];

    if (bucket.last_checked == 0) {
        // First request, initialize
        bucket = {1.0, now};  
        return true;
    }

    double elapsed = (now - bucket.last_checked) / 1000.0; // seconds
    bucket.tokens = max(0.0, bucket.tokens - elapsed * leak_rate); // Leak over time
    bucket.last_checked = now;

    if (bucket.tokens < bucket_capacity) {
        bucket.tokens += 1.0; 
        return true;
    }

    return false; 
}
