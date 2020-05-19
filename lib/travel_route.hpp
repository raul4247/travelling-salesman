#include "../lib/graph.hpp"
#include <string>

using std::pair;
using std::string;
using graph::Graph;

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
            string to_string();
    };
}