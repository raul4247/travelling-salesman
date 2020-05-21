#include <bits/stdc++.h>
#include "../lib/Utils.hpp"
#include "../lib/Graph.hpp"
#include "../lib/Point.hpp"
#include "../lib/TSPAlgorithms.hpp"
#include "../lib/InputManager.hpp"
#include <chrono> 
#include "../lib/Utils.hpp"

using Utils = TravelingSalesman::Utils;

#define INPUT_FILE_PATH(n) ("../inputs/vertices_" + n + ".in")

using namespace std;
using namespace std::chrono; 
using Point = TravelingSalesman::Point;
using Graph = TravelingSalesman::Graph;
using BruteForce = TravelingSalesman::BruteForce;
using BranchAndBound = TravelingSalesman::BranchAndBound;
using Dynamic = TravelingSalesman::Dynamic;
using InputManager = TravelingSalesman::InputManager;


int main(int argc, char *argv[])
{
    char op;
    do
    {
        cout << "Traveling Salesman Solver:\n";
        cout << "1. Gen random inputs [1..100]\n";
        cout << "2. Brute Force through inputs[1..100]\n";
        cout << "3. Branch and Bound through inputs[1..100]\n\n";
        cout << "4. Dynamic through inputs[1..100]\n\n";
        cout << "0. Exit\n\n";
        cout << "OP: ";

        cin >> op;
        switch (op)
        {
        case '1':
        {
            InputManager::genAllAllowedRandomInputs();
            break;
        }
        case '2':
        {
            BruteForce bruteForce;
            bruteForce.runInRange(1, 100);
            break;
        }
        case '3':
        {
            BranchAndBound branchAndBound;
            branchAndBound.runInRange(1, 100);
            break;
        }
        case '4':
            Dynamic dynamic;
            dynamic.runInRange(1,100);
            break;
        }
    } while (op != '0');

    return 0;
}