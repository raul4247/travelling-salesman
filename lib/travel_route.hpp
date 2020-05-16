#include "../lib/graph.hpp"

using std::pair;
using namespace graph;

namespace travel_route {
    class TravelRoute {
        private:
            // Grafo que armazena a distancia para cada cidade
            Graph *cities;
            vector<int> *route;
            double fitness = 0.0;
            double distance = 0.0;
        public:
            TravelRoute(vector<pair<int, int>> cities);
            ~TravelRoute();
            double get_distance();
            double get_fitness();
            void generate_individual();
    };
}