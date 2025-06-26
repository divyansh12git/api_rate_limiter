#include "FixedWindowLimiter.hpp"
#include <chrono>

FixedWindowLimiter::FixedWindowLimiter(int limit, int window)
    : max_requests(limit), window_size(window) {}

bool FixedWindowLimiter::allowRequest(const std::string& user_id) {

    auto now = std::chrono::system_clock::now().time_since_epoch();
    long long current_time = std::chrono::duration_cast<std::chrono::seconds>(now).count();
    
    long long window_start = current_time - (current_time % window_size);

    auto& entry = user_data[user_id];
    if (entry.second != window_start) {
        entry = {1, window_start};  // reset
        return true;
    }

    if (entry.first < max_requests) {
        entry.first++;
        return true;
    }

    return false;
}



// use the actual unix timestamp suppose 5req/10 sec-->
// divide time in 10 sec windows and currenttime-(current%win_Size) gives which time window is it
// if it's wntry there in map inc count else decrease
// return if cnt<max_request