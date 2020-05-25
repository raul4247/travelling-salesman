#ifndef TSP_ALGORITHMS_H
#define TSP_ALGORITHMS_H

#include <string>
#include <cfloat>
#include <sstream>
#include "../lib/input_manager.hpp"
#include "../lib/timer.hpp"
#include "../lib/graph.hpp"
#include "../lib/TSP_result.hpp"
#include "../lib/utils.hpp"
#include "../lib/travel_route.hpp"
#include "../lib/population.hpp"

#define SAMPLES 10

using genetic::TravelRoute;
using genetic::Population;

namespace traveling_salesman
{
    class BruteForce
    {
        private:
            double weigth_of_path(int *path, int size);
            void permutation(int *arr, int i, int n);
            Graph* graph;

        public:
            double min_dist;
            int *min_path;
            long long run(int);
            // O metodo que executa nosso algoritmo x vezes, sendo esse x a diferença de end e begin.
            void run_in_range(int, int);
            // O metodo que executa nosso algoritmo x vezes, sendo esse x a diferença de end e begin colocando em uma arquivo os dados para estatitica.
            void run_in_range_statistic(int, int);
    };

    class BranchAndBound
    {
        private:
            double weigth_of_path(int *path, int size);
            void permutation(int *arr, int i, int n);
            double calculate_lower_bound(int n);
            Graph* graph;
        public:
            double lower_bound;
            double min_dist;
            int *min_path;
            long long run(int);
            // O metodo que executa nosso algoritmo x vezes, sendo esse x a diferença de end e begin.
            void run_in_range(int, int);
            // O metodo que executa nosso algoritmo x vezes, sendo esse x a diferença de end e begin colocando em uma arquivo os dados para estatitica.
            void run_in_range_statistic(int, int);
    };

    class Dynamic
    {
        private:

            // algoritmo que calcula de forma dinamica o menor caminho
            double tsd(int mask, int pos);
            // O metodo a seguir inicializa as estruturas que vamos usar para calcular o menor caminho
            void start();
            // O metodo a seguir coloca em um vetor o menor caminho encontrado pelo algoritmo.
            int* display_path(int source);
            Graph* graph;

        public:
            // Matrix onde estara armazenado o menor caminho que o algoritmo ira encontrar
            int **path;
            // Variavel para guardar o valor da menor distancia
            double min_path;
            // Variavel que guardar a quantidade das minhas cidades
            int size;
            // Matrix auxiliar para calcular o menor caminho 
            double **dp;
            // Variavel para guardar a posicao em que estou(a cidade atual)
            int pos;
            // Variavel que marcar que ja visitei a cidade
            int visited;
            
            long long run(int);
            // O metodo que executa nosso algoritmo x vezes, sendo esse x a diferença de end e begin.
            void run_in_range(int, int);
            // O metodo que executa nosso algoritmo x vezes, sendo esse x a diferença de end e begin colocando em uma arquivo os dados para estatitica.
            void run_in_range_statistic(int, int);
    };

    class Genetic
    {
        private:
            static const double mutation_rate;
            static const int tournament_size;
            static const int population_size;
            static const int generations;
            // Manter a melhor rota a cada chamada de evolve_population
            static const bool elitism;
            static Population evolve_population(Population p);
            static TravelRoute crossover(TravelRoute a, TravelRoute b);
            static void mutate(TravelRoute &tr);
            static TravelRoute tournament_selection(Population p);
        public:
            long long run(int);
            void run_in_range(int, int);
            void run_in_range_statistic(int, int);
    };
}
#endif // TSP_ALGORITHMS_H