#ifndef TSP_ALGORITHMS_H
#define TSP_ALGORITHMS_H

#include <string>
#include <cfloat>
#include "../lib/input_manager.hpp"
#include "../lib/timer.hpp"
#include "../lib/graph.hpp"
#include "../lib/TSP_result.hpp"
#include "../lib/utils.hpp"
#include "../lib/travel_route.hpp"
#include "../lib/graph2.hpp"
#include "../lib/population.hpp"

using genetic::TravelRoute;
using genetic::Population;

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

    class Dynamic
    {
        private:
            double weigth_of_path(int *path, int size, double **matrix);
            double tsd(int mask, int pos);
            void start();
            int* display_path(int source);

        public:
            double min_dist;
            int **path;
            double min_path;
            double **matrix;
            int size;
            double **dp;
            int pos;
            int visited;
            void run(int);
            void run_in_range(int, int);
    };

    class Genetic
    {
        private:
            static constexpr double mutation_rate = 0.015;
            static constexpr int tournament_size = 5;
            // Manter a melhor roda a cada chamada de evolve_population
            static constexpr bool elitism = true;
            static Population evolve_population(Population p);
            static TravelRoute crossover(TravelRoute a, TravelRoute b);
            static void mutate(TravelRoute &tr);
            static TravelRoute tournament_selection(Population p);
        public:
            void run(int);
            void run_in_range(int, int);
    };
}
#endif // TSP_ALGORITHMS_H