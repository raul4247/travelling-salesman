#include <bits/stdc++.h>
#include <chrono>
#include "../lib/utils.hpp"
#include "../lib/graph.hpp"
#include "../lib/point.hpp"
#include "../lib/TSP_algorithms.hpp"
#include "../lib/input_manager.hpp"
#include "../lib/utils.hpp"

#define INPUT_FILE_PATH(n) ("../inputs/vertices_" + n + ".in")

using std::cout;
using std::cin;
using namespace traveling_salesman;

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
                InputManager::gen_all_allowed_random_inputs();
                break;
            case '2':
                BruteForce bruteForce;
                bruteForce.run_in_range(1, 100);
                break;
            case '3':
                BranchAndBound branchAndBound;
                branchAndBound.run_in_range(1, 100);
                break;
            case '4':
                Dynamic dynamic;
                dynamic.run_in_range(1,100);
                break;
        }
    } while (op != '0');

    return 0;
}
