#ifndef POPULATION_H
#define POPULATION_H

#include "travel_route.hpp"

namespace genetic {
    class Population {
        private:
            vector<TravelRoute> *routes;
        public:
            Population(int capacity);
            void save_route(int idx, TravelRoute route);
            TravelRoute& get_route(int idx);
            TravelRoute get_best_route();
            int size();
    };
}
#endif // POPULATION_H