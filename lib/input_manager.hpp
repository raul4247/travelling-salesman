#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <fstream>
#include <math.h>
#include <time.h>

#include "../lib/point.hpp"
#include "../lib/graph.hpp"
#include "../lib/travel_route.hpp"

#define INPUT_FILE_PATH(n) ("../inputs/vertices_" + n + ".in")
#define OUTPUT_CSV_PATH(algorithm) ("../outputs/" + algorithm + ".csv")
#define OUTPUT_FILE_PATH(algorithm) ("../outputs/" + algorithm + ".out")
#define MAX_N 100
#define MAX_XY 1000

namespace traveling_salesman
{
    class InputManager
    {
        private:
            static vector<Point> gen_points(int);
            static void gen_random_input(int);

        public:
            static void gen_all_allowed_random_inputs();
            static Graph* read_graph_in_file(int);
            static vector<City> read_cities_in_file(int);
    };
}
#endif
