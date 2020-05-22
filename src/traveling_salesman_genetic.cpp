#include "../lib/genetic_algorithm.hpp"
#include <iostream>

using namespace std;
using namespace graph;
using namespace travel_route;
using namespace genetic_algorithm;

int main(){
    int num_cities {};

    cin >> num_cities;
    vector<pair<int,int>> cities(num_cities);

    for(auto &city : cities){
        cin >> city.first;
        cin >> city.second;
    }

    Population cobaia(50);


    for(int i = 0; i < 50; i++){
        TravelRoute tr(cities);
        tr.generate_individual();
        tr.print();
        cobaia.save_route(i, tr);
    }

    cout << "distancia inicial: " << cobaia.get_best_route().get_distance() << endl;

    cobaia = GeneticAlgorithm::evolve_population(cobaia);
    // Evolui a cobaia por 100 geracoes
    for(int i = 0; i <= 100; i++){
        cobaia = GeneticAlgorithm::evolve_population(cobaia);
    }


    cout << "resultado: " << cobaia.get_best_route().get_distance() << endl;
    cobaia.get_best_route().print();

    return 0;
}