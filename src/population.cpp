#include "../lib/population.hpp"

namespace population {

    Population::Population(int capacity){
        this->routes = new vector<TravelRoute>(capacity);
    }

    Population::~Population(){
        delete this->routes;
        this->routes = nullptr;
    }

    void Population::save_route(int idx, TravelRoute route){
        this->routes->at(idx) = route;
    }

    TravelRoute Population::get_route(int idx){
       return this->routes->at(idx);
    }

    TravelRoute Population::get_best_route(){
        TravelRoute best = this->routes->front();
        for(auto route: *this->routes){
            if(route.get_fitness() >= best.get_fitness()){
                best = route;
            }
        }
        return best;
    }

    int Population::length(){
        return this->routes->size();
    }

}