#include "../lib/graph.hpp"
#include <iostream>

using namespace std;
using namespace graph;

int main(){
    int num_cities {};

    cin >> num_cities;
    vector<pair<int,int>> cities(num_cities);

    for(auto &city : cities){
        cin >> city.first;
        cin >> city.second;
    }

    Graph *g = new Graph(num_cities);
    for(int i = 1; i <= num_cities; ++i){
        auto cityA = cities.at(i);
        for(int j = 1; j <= num_cities; ++j){
            if(i != j){
                auto cityB = cities.at(j);
                auto xs = pow(abs(cityB.first - cityA.first),2);
                auto ys = pow(abs(cityB.second - cityA.second),2);
                double distance = sqrt(xs + ys);
                g->add_conection(i, j, distance);
            }
        }
    }

    return 0;
}