#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

#include "../lib/Point.hpp"
#include "../lib/Graph.hpp"
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <fstream>
#include <math.h>
#include <time.h>

#define INPUT_FILE_PATH(n) ("../inputs/vertices_" + n + ".in")
#define OUTPUT_FILE_PATH(algorithm) ("../outputs/" + algorithm + ".csv")
#define MAX_N 100
#define MAX_XY 1000

namespace TravelingSalesman
{
    class InputManager
    {
    private:
        static std::vector<Point> genPoints(int);
        static void genRandomInput(int);

    public:
        static void genAllAllowedRandomInputs();
        static Graph readGraphInFile(int);
    };
} 
#endif
