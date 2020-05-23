#include "../lib/population.hpp"

namespace population {

    Population::Population(int capacity){
        this->routes = new vector<TravelRoute>(capacity);
    }

    void Population::save_route(int idx, TravelRoute route){
        this->routes->at(idx) = route;
    }

    TravelRoute& Population::get_route(int idx){
       return this->routes->at(idx);
    }

    TravelRoute Population::get_best_route(){
        TravelRoute best = this->routes->at(0);
        for(auto route: *this->routes){
            if(route.get_fitness() >= best.get_fitness()){
                best = route;
            }
        }
        return best;
    }

    int Population::size(){
        return this->routes->size();
    }

}