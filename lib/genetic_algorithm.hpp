#include "../lib/population.hpp"

using population::Population;

namespace genetic_algorithm {
    class GeneticAlgorithm {
        private:
            static const double mutation_rate = 0.015;
            static const int tournament_size = 5;
            // Manter a melhor roda a cada chamada de evolve_population
            static const bool elitism = true;
        public:
            static Population evolve_population(Population p);
            static TravelRoute crossover(TravelRoute a, TravelRoute b);
            static void mutate(TravelRoute &tr);
            static TravelRoute tournament_selection(Population p);
    };
}