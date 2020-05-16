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

    return 0;
}