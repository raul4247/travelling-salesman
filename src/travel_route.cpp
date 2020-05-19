#include "../lib/travel_route.hpp"
#include <random>
#include <algorithm>

using std::pair;
using std::random_shuffle;

namespace travel_route {
    TravelRoute::TravelRoute(vector<pair<int,int>> cities){
        // Caminho atual a ser percorrido
        this->route = new vector<int>(cities.size());
        this->cities = new Graph(cities.size());

        for(int i = 0; i < cities.size(); ++i){
            this->route->at(i) = i + 1;
            auto cityA = cities.at(i);
            for(int j = 0; j < cities.size(); ++j){
                if(i != j){
                    auto cityB = cities.at(j);
                    double xs = pow(cityB.first - cityA.first,2);
                    double ys = pow(cityB.second - cityA.second,2);
                    this->cities->add_conection(i, j, sqrt(xs + ys));
                }
            }
        }
    }

    double TravelRoute::get_distance(){
        if(this->distance == 0.0){
            for(int i = 0; i < this->route->size() - 1; ++i){
                this->distance += cities->get_conection(route->at(i), route->at(i + 1));
            }
            // Adiciona a distancia para voltar a cidade inicial
            this->distance += cities->get_conection(route->front(), route->back());
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

    string TravelRoute::to_string(){

    }
}