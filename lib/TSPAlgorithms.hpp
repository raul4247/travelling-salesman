#ifndef TSP_ALGORITHMS
#define TSP_ALGORITHMS

#include <string>
#include <cfloat>
#include "../lib/TSPResult.hpp"
#include "../lib/InputManager.hpp"
#include "../lib/Timer.hpp"
#include "../lib/Graph.hpp"
#include "../lib/TSPResult.hpp"
#include "../lib/Utils.hpp"

namespace TravelingSalesman
{
    class BruteForce
    {
        private:
            double weigthOfPath(int *path, int size, double **matrix);
            void permutation(int *arr, int i, int n, double **matrix);

        public:
            double minDist;
            int *minPath;
            void run(int);
            void runInRange(int, int);
    };

    class BranchAndBound
    {
        private:
            double weigthOfPath(int *path, int size, double **matrix);
            void permutation(int *arr, int i, int n, double **matrix);
            double calculateLowerBound(double **matrix, int n);

        public:
            double lowerBound;
            double minDist;
            int *minPath;
            void run(int);
            void runInRange(int, int);
    };
}
#endif