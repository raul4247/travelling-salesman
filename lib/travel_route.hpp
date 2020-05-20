#include "../lib/graph.hpp"
#include <string>

using std::pair;
using std::string;
using graph::Graph;

namespace travel_route {
    class TravelRoute {
        private:
            // Vetor que armanena a rota a ser percorrida
            // Apartir dela indexamos a posicao no cities_dist e cities
            vector<int> *route;
            // Grafo que armazena a distancia para cada cidade
            Graph *cities_dist;
            // Vetor que armanena as cidades correspondentes a rota.
            vector<pair<int, int>> *cities;
            double fitness = 0.0;
            double distance = 0.0;
        public:
            TravelRoute(vector<pair<int, int>> cities);
            ~TravelRoute();
            double get_distance();
            double get_fitness();
            void generate_individual();
            bool contains_city(pair<int,int> city);
            pair<int, int> get_city(int route_position);
            void swap_cities(int route_pos1, int route_pos2);
            int size();
            string to_string();
    };
}