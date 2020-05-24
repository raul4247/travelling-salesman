#include <bits/stdc++.h>
#include <chrono>
#include "../lib/utils.hpp"
#include "../lib/graph.hpp"
#include "../lib/point.hpp"
#include "../lib/TSP_algorithms.hpp"
#include "../lib/input_manager.hpp"
#include "../lib/utils.hpp"

#define INPUT_FILE_PATH(n) ("../inputs/vertices_" + n + ".in")

using std::cin;
using std::cout;
using namespace traveling_salesman;

int main(int argc, char *argv[])
{
    BruteForce bruteForce;
    BranchAndBound branchAndBound;
    Dynamic dynamic;
    Genetic genetic;

    char op;
    do
    {
        cout << "Traveling Salesman Solver:\n";
        cout << "1. Gen random inputs [1..100]\n";
        cout << "2. Brute Force through inputs[1..100]\n";
        cout << "3. Branch and Bound through inputs[1..100]\n";
        cout << "4. Dynamic through inputs[1..100]\n";
        cout << "5. Genetic through inputs[1..100]\n";
        cout << "6. Brute Force statistics[1..100]\n";
        cout << "7. Branch and Bound statistics[1..100]\n";
        cout << "8. Dynamic statistics[1..100]\n";
        cout << "9. Genetic statistics[1..100]\n";
        cout << "0. Exit\n\n";
        cout << "OP: ";

        cin >> op;
        switch (op)
        {
        case '1':
            InputManager::gen_all_allowed_random_inputs();
            break;
        case '2':
            bruteForce.run_in_range(1, 100);
            break;
        case '3':
            branchAndBound.run_in_range(1, 100);
            break;
        case '4':
            dynamic.run_in_range(1, 100);
            break;
        case '5':
            genetic.run_in_range(1, 100);
            break;
        case '6':
            bruteForce.run_in_range_statistic(1, 100);
            break;
        case '7':
            branchAndBound.run_in_range_statistic(1, 100);
            break;
        case '8':
            dynamic.run_in_range_statistic(1, 100);
            break;
        case '9':
            genetic.run_in_range_statistic(1, 100);
            break;
        }
    } while (op != '0');

    return 0;
}
