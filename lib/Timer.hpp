#ifndef TIMER
#define TIMER

#include <chrono>

using namespace std::chrono;

namespace TravelingSalesman
{
    class Timer
    {
        public:
            high_resolution_clock::time_point begin, end;

            void start()
            {
                Timer::begin = high_resolution_clock::now();
            }

            long long stop()
            {
                Timer::end = high_resolution_clock::now();
                return duration_cast<microseconds>(Timer::end - Timer::begin).count();
            }
    };
}

#endif
