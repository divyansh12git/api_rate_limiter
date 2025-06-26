// #error "binding.cpp is being compiled"
#include "napi.h"
using namespace Napi;
#include "limiters/FixedWindowLimiter.hpp"
#include "limiters/SlidingLogLimiter.hpp"
#include "limiters/TokenBucketLimiter.hpp"
#include "limiters/LeakyBucketLimiter.hpp"

// Initialize all limiter instances
FixedWindowLimiter fixedLimiter(5, 10);
SlidingLogLimiter slidingLimiter(5, 10);
TokenBucketLimiter tokenLimiter(5, 1.0);
LeakyBucketLimiter leakyLimiter(5, 1);



String HelloWorld(const CallbackInfo& info) {
    Env env = info.Env();
    return String::New(env, "Hello from C++ addon!");
}
// Wrapper functions

Boolean CheckFixed(const CallbackInfo& info) {
    Env env = info.Env();
    std::string user_id = info[0].As<String>();
    bool allowed = fixedLimiter.allowRequest(user_id);
    return Boolean::New(env, allowed);
}

Boolean CheckSliding(const CallbackInfo& info) {
    Env env = info.Env();
    std::string user_id = info[0].As<String>();
    bool allowed = slidingLimiter.allowRequest(user_id);
    return Boolean::New(env, allowed);
}

Boolean CheckToken(const CallbackInfo& info) {
    Env env = info.Env();
    std::string user_id = info[0].As<String>();
    bool allowed = tokenLimiter.allowRequest(user_id);
    return Boolean::New(env, allowed);
}

Boolean CheckLeaky(const CallbackInfo& info) {
    Env env = info.Env();
    std::string user_id = info[0].As<String>();
    bool allowed = leakyLimiter.allowRequest(user_id);
    return Boolean::New(env, allowed);
}

// Module init
Object Init(Env env, Object exports) {
    exports.Set("checkFixed", Function::New(env, CheckFixed));
    exports.Set("checkSliding", Function::New(env, CheckSliding));
    exports.Set("checkToken", Function::New(env, CheckToken));
    exports.Set("checkLeaky", Function::New(env, CheckLeaky));
    exports.Set("helloWorld", Function::New(env, HelloWorld));
    return exports;
}

NODE_API_MODULE(api_rate_limiter, Init)
