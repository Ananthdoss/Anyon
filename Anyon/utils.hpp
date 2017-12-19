#pragma once

#include <string>
#include <chrono>
#include "types.hpp"

namespace Anyon
{
    inline auto GetPerfTimer()
    {
        using namespace std::chrono;
        typedef std::conditional_t<high_resolution_clock::is_steady, high_resolution_clock, steady_clock> clock;
        return clock::now().time_since_epoch();
    }
    
    template<class Duration>
    inline auto GetPerfTimer()
    {
        return std::chrono::duration_cast<Duration>(GetPerfTimer());
    }
}
