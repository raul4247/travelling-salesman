#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

#include "../lib/Point.hpp"
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <fstream>
#include <math.h>
#include <time.h>

#define INPUT_FILE_PATH(n) ("../inputs/vertices_" + n + ".in")
#define MAX_N 100
#define MAX_XY 1000

using namespace std;

namespace TravelingSalesman
{
    class InputManager;

    class InputManager
    {
    private:
        static vector<Point> genPoints(int n);
        static void genRandomInput(int vertexCount);

    public:
        static void genAllAllowedRandomInputs();
    };
} 
#endif
