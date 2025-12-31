#pragma once

#include <iostream>
#include <chrono>
#include <thread>

namespace color 
{
    constexpr const char* x = "\033[0m";    // reset
    constexpr const char* r = "\033[31m";   // red
    constexpr const char* g = "\033[32m";   // green
    constexpr const char* y = "\033[33m";   // yellow
    constexpr const char* b = "\033[34m";   // blue
    constexpr const char* m = "\033[35m";   // magenta
    constexpr const char* c = "\033[36m";   // cyan
}

namespace utils
{    
    void sleep_ms(int ms)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(ms));
    };

}
