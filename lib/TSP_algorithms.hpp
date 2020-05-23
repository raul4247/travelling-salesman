#ifndef TSP_ALGORITHMS_H
#define TSP_ALGORITHMS_H

#include <string>
#include <cfloat>
#include "../lib/input_manager.hpp"
#include "../lib/timer.hpp"
#include "../lib/graph.hpp"
#include "../lib/TSP_result.hpp"
#include "../lib/utils.hpp"

namespace traveling_salesman
{
    class BruteForce
    {
        private:
            double weigth_of_path(int *path, int size, double **matrix);
            void permutation(int *arr, int i, int n, double **matrix);

        public:
            double min_dist;
            int *min_path;
            void run(int);
            void run_in_range(int, int);
    };

    class BranchAndBound
    {
        private:
            double weigth_of_path(int *path, int size, double **matrix);
            void permutation(int *arr, int i, int n, double **matrix);
            double calculate_lower_bound(double **matrix, int n);

        public:
            double lower_bound;
            double min_dist;
            int *min_path;
            void run(int);
            void run_in_range(int, int);
    };
}
#endif // TSP_ALGORITHMS_H