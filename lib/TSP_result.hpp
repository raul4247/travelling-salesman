#ifndef TSP_RESULT_H
#define TSP_RESULT_H
#define llong long long

#include "../lib/input_manager.hpp"
#include <iostream>
#include <iomanip>
#include <string>

using std::string;

namespace traveling_salesman
{
    class TSPResult
    {
        private:
            int input_size;
            double min_dist;
            int *min_path;
            llong time_taken_in_microseconds;
        public:
            TSPResult(int, double, int*, llong);
            void show_result(string);
    };
}

#endif // TSP_RESULT_H