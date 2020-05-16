#include "../lib/travel_route.hpp"

using std::pair;

namespace travel_route {
    TravelRoute::TravelRoute(vector<pair<int,int>> cities){

        // Caminho atual a ser percorrido
        this->tour = new vector<int>(cities.size());
        this->cities = new Graph(cities.size());

        for(int i = 0; i < cities.size(); ++i){
            this->tour->at(i) = i + 1;
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
        double distance = 0;
        for(int i = 0; i < this->tour->size() - 1; ++i){
            distance += cities->get_conection(tour->at(i), tour->at(i + 1));
        }
        // Adiciona a distancia para voltar a cidade inicial
        distance += cities->get_conection(tour->front(), tour->back());
        return distance;
    }
}