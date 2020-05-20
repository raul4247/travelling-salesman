#include "../lib/travel_route.hpp"
#include <random>
#include <algorithm>

using std::pair;
using std::random_shuffle;
using std::iter_swap;

namespace travel_route {
    TravelRoute::TravelRoute(vector<pair<int,int>> cities){
        this->route = new vector<int>(cities.size());
        this->cities_dist = new Graph(cities.size());
        this->cities = &cities;

        for(int i = 0; i < cities.size(); ++i){
            this->route->at(i) = i;
            auto cityA = cities.at(i);
            for(int j = 0; j < cities.size(); ++j){
                if(i != j){
                    auto cityB = cities.at(j);
                    double xs = pow(cityB.first - cityA.first,2);
                    double ys = pow(cityB.second - cityA.second,2);
                    this->cities_dist->add_conection(i, j, sqrt(xs + ys));
                }
            }
        }
    }

    double TravelRoute::get_distance(){
        if(this->distance == 0.0){
            for(int i = 0; i < this->route->size() - 1; ++i){
                this->distance += cities_dist->get_conection(route->at(i), route->at(i + 1));
            }
            // Adiciona a distancia para voltar a cidade inicial
            this->distance += cities_dist->get_conection(route->front(), route->back());
        }
        return this->distance;
    }

    double TravelRoute::get_fitness(){
        if(this->fitness == 0.0){
            this->fitness = 1/this->get_distance();
        }
        return this->fitness;
    }

    void TravelRoute::generate_individual(){
        random_shuffle(this->route->begin(), this->route->end());
    }

    bool TravelRoute::contains_city(pair<int,int> city){
        bool contains = false;
        for(auto c : *this->cities){
            if(c == city){
                contains = true;
                break;
            }
        }
        return contains;
    }

    pair<int,int> TravelRoute::get_city(int route_position){
        return this->cities->at(this->route->at(route_position));
    }

    int TravelRoute::size(){
        return this->route->size();
    }

    void TravelRoute::swap_cities(int route_pos1, int route_pos2){
        auto begin = this->route->begin();
        iter_swap(begin + route_pos1, begin + route_pos2);
    }

    string TravelRoute::to_string(){
        string route {};
        for(auto city : *this->route) {
            route += (city + 1) + " ";
        }
        return route;
    }
}