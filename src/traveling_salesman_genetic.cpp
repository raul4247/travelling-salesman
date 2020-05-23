#include "../lib/genetic_algorithm.hpp"
#include <iostream>

using namespace std;
using namespace graph;
using namespace travel_route;
using namespace genetic_algorithm;

int main(){
    int num_cities {};

    cin >> num_cities;
    vector<City> cities(num_cities);

    int id = 0;
    for(auto &city : cities){
        cin >> city.coord.first;
        cin >> city.coord.second;
        city.id = id++;
    }

    Population cobaia(50);

    for(int i = 0; i < 50; i++){
        TravelRoute tr(cities);
        tr.generate_individual();
        cobaia.save_route(i, tr);
    }

    TravelRoute best = cobaia.get_best_route();

    cout << "distancia inicial: " << best.get_distance() << endl;

    cobaia = GeneticAlgorithm::evolve_population(cobaia);
    // Evolui a cobaia por 100 geracoes
    for(int i = 0; i <= 10; i++){
        cobaia = GeneticAlgorithm::evolve_population(cobaia);
    }

    best = cobaia.get_best_route();
    cout << "resultado: " << best.get_distance() << endl;
    best.print_order();
    best.print_cities();

    return 0;
}