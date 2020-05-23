#ifndef TIMER_H
#define TIMER_H

#include <chrono>

using std::chrono::high_resolution_clock;
using std::chrono::duration_cast;
using std::chrono::microseconds;

namespace traveling_salesman
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

#endif // TIMER_H