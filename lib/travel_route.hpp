#ifndef TRAVEL_ROUTE_H
#define TRAVEL_ROUTE_H

#include <string>
#include <random>
#include <algorithm>
#include "graph.hpp"
#include "point.hpp"

using std::pair;
using std::string;
using std::random_device;
using std::default_random_engine;
using traveling_salesman::Graph;
using City = traveling_salesman::Point;

namespace genetic {
    class TravelRoute
    {
        private:
            // Vetor que armanena a rota a ser percorrida
            // Apartir dela indexamos a posicao no cities_dist e cities
            vector<int> *route = nullptr;
            // Grafo que armazena a distancia para cada cidade
            Graph *cities_dist = nullptr;
            // Vetor que armanena as cidades correspondentes a rota.
            vector<City> *cities = nullptr;
            double fitness = 0.0;
            double distance = 0.0;

        public:
            TravelRoute(vector<City> cities);
            TravelRoute();
            double get_distance();
            double get_fitness();
            void generate_individual();
            bool contains_city(City city);
            City get_city(int route_position);
            void swap_cities(int route_pos1, int route_pos2);
            int size();
            void print_order();
            void print_cities();
            int* get_route();

            // static random generator
            static default_random_engine rng;
    };
}
#endif // TRAVEL_ROUTE_H