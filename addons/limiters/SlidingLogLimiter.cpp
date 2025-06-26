#include "SlidingLogLimiter.hpp"
#include <chrono>

SlidingLogLimiter::SlidingLogLimiter(int limit, int window)
    : max_requests(limit), window_size(window) {}

bool SlidingLogLimiter::allowRequest(const std::string& user_id) {
    long long now = std::chrono::duration_cast<std::chrono::seconds>(
                        std::chrono::system_clock::now().time_since_epoch())
                        .count();

    auto& logs = user_logs[user_id];

    while (!logs.empty() && now - logs.front() > window_size)
        logs.pop_front();

    if (logs.size() < max_requests) {
        logs.push_back(now);
        return true;
    }

    return false;
}

// dividing 5req/10secs use deque to store time the now is the current time of req
// now-dq.front is the time elapsed if it is more then pop the elements form window 
//and if window size<max store current req and push in dq else reject