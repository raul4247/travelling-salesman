#include "../lib/travel_route.hpp"
#include <algorithm>
#include <random>
#include <iostream>

using std::pair;
using std::shuffle;
using std::iter_swap;

namespace travel_route {
    std::random_device rd {};
    default_random_engine TravelRoute::rng {rd()};

    TravelRoute::TravelRoute(vector<pair<int,int>> cities){
        this->route = new vector<int>(cities.size());
        this->cities_dist = new Graph(cities.size());
        this->cities = new vector<pair<int,int>>(cities);

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

    TravelRoute::TravelRoute(){
        this->route = nullptr;
        this->cities_dist = nullptr;
        this->cities = nullptr;
    }

    double TravelRoute::get_distance(){
        if(this->distance == 0.0){
            if(this->route != nullptr && this->route->size() > 0){
                for(int i = 0; i < this->route->size() - 1; ++i){
                    this->distance += cities_dist->get_conection(route->at(i), route->at(i + 1));
                }
                // Adiciona a distancia para voltar a cidade inicial
                this->distance += cities_dist->get_conection(route->front(), route->back());
            }
        }
        return this->distance;
    }

    double TravelRoute::get_fitness(){
        if(this->fitness == 0.0){
            double distance = this->get_distance();
            if(distance > 0){
                this->fitness = 1/distance;
            }
        }
        return this->fitness;
    }

    void TravelRoute::generate_individual(){
        if(this->route != nullptr){
            shuffle(this->route->begin(), this->route->end(), this->rng);
            this->distance = 0.0;
            this->fitness = 0.0;
        }
    }

    bool TravelRoute::contains_city(pair<int,int> city){
        bool contains = false;
        if(this->cities != nullptr){
            for(auto c : *this->cities){
                if(c == city){
                    contains = true;
                    break;
                }
            }
        }
        return contains;
    }

    pair<int,int> TravelRoute::get_city(int route_position){
        return this->cities->at(this->route->at(route_position));
    }

    int TravelRoute::size(){
        int size {};
        if(this->route != nullptr){
            size = this->route->size();
        }
        return size;
    }

    void TravelRoute::swap_cities(int route_pos1, int route_pos2){
        if(this->route != nullptr){
            auto begin = this->route->begin();
            iter_swap(begin + route_pos1, begin + route_pos2);
            // Como a rota foi alterada, a distancia deve ser recalculada.
            this->distance = 0.0;
            this->fitness = 0.0;
        }
    }

    void TravelRoute::print(){
        if(this->route != nullptr){
            for(auto const &city : *this->route){
                std::cout << city + 1 << " ";
            }
            std::cout << std::endl;
        }
    }
}