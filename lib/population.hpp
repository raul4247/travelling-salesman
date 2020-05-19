#include "../lib/travel_route.hpp"

using travel_route::TravelRoute;

namespace population {
    class Population {
        private:
            vector<TravelRoute> *routes;
        public:
            Population(int capacity);
            ~Population();
            void save_route(int idx, TravelRoute route);
            TravelRoute get_route(int idx);
            TravelRoute get_best_route();
            int length();
    };
}