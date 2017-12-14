#pragma once

#include <string>
#include <chrono>

namespace Anyon
{
    inline auto GetPerfTimer() noexcept
    {
        using namespace std::chrono;
        typedef std::conditional_t<high_resolution_clock::is_steady, high_resolution_clock, steady_clock> clock;
        return clock::now().time_since_epoch();
    }
    
    template<class Duration>
    inline auto GetPerfTimer() noexcept
    {
        return std::chrono::duration_cast<Duration>(GetPerfTimer());
    }
    
    template <typename T>
    T Argument(T value) noexcept
    {
        return value;
    }
    template <typename T>
    T const * Argument(std::basic_string<T> const & value) noexcept
    {
        return value.c_str();
    }
    template <typename ... Args>
    inline void Print(char const * const format, Args const & ... args) noexcept
    {
    #ifdef __APPLE__
        extern int NSLogPrintf(const char * __restrict format, ...);
        NSLogPrintf(format, Argument(args) ...);
    #else
        printf(format, Argument(args) ...);
    #endif
    }
}
