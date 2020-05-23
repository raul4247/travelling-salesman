#ifndef TSP_RESULT
#define TSP_RESULT

#include <iostream>
#include <iomanip>
#include <string>

namespace TravelingSalesman
{
    class TSPResult
    {
        private:
            int inputSize;
            double minDist;
            int *minPath;
            long long timeTakenInMicroseconds;
        public:
            TSPResult(int, double, int*, long long);
            void showResult(std::string);
    };
}

#endif