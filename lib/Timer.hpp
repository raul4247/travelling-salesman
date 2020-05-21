#ifndef TIMER
#define TIMER

#include <chrono>

namespace TravelingSalesman
{
    class Timer
    {
    public:
        std::chrono::high_resolution_clock::time_point begin, end;

        void start()
        {
            Timer::begin = std::chrono::high_resolution_clock::now();
        }

        long long stop()
        {
            Timer::end = std::chrono::high_resolution_clock::now();
            return std::chrono::duration_cast<std::chrono::microseconds>(Timer::end - Timer::begin).count();
        }
    };
}

#endif
