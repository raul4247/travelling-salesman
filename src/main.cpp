#include <bits/stdc++.h>
#include "../lib/Graph.hpp"
#include "../lib/Point.hpp"
#include "../lib/InputManager.hpp"

#define INPUT_FILE_PATH(n) ("../inputs/vertices_" + n + ".in")

using namespace std;
using Point = TravelingSalesman::Point;
using Graph = TravelingSalesman::Graph;
using InputManager = TravelingSalesman::InputManager;

double minDist = DBL_MAX;
int *minPath;

int *copyArr(int *src, int size)
{
    int *dest = new int[size];
    for (int i = 0; i < size; i++)
        dest[i] = src[i];
    return dest;
}

double weigthOfPath(int *path, int size, double **matrix)
{
    double weight = 0.0;

    for (int i = 1; i < size; i++)
        weight += matrix[path[i]][path[i - 1]];
    weight += matrix[path[size - 1]][0];

    return weight;
}

void permutation(int *arr, int i, int n, double **matrix)
{
    if (i == n)
    {
        double w = weigthOfPath(arr, n, matrix);
        if (w <= minDist)
        {
            delete[] minPath;
            minPath = copyArr(arr, n);
            minDist = w;
        }
        return;
    }

    for (int j = i; j < n; j++)
    {
        swap(arr[i], arr[j]);
        permutation(arr, i + 1, n, matrix);
        swap(arr[i], arr[j]);
    }
}

void bruteForce()
{
    for (int k = 1; k <= 100; k++)
    {
        cout << "Entrada de tamanho: " << k << endl;
        fstream inputFile(INPUT_FILE_PATH(to_string(k)), ios_base::in);

        int n;
        inputFile >> n;

        int *graphPath = new int[n];
        Graph graph(n);

        for (int i = 0; i < n; i++)
        {
            int x, y;
            inputFile >> x >> y;
            graph.addPoint(Point(x, y));
            graphPath[i] = i;
        }

        permutation(graphPath, 1, n, graph.matrix);

        cout << "Min: " << minDist << endl;
        cout << "Min path: ";
        for (int i = 0; i < n; i++)
            cout << minPath[i] << " ";
        cout << endl
             << endl;

        minDist = DBL_MAX;
        delete[] graphPath;
    }
}

int main(int argc, char *argv[])
{
    char op;
    do
    {
        cout << "Traveling Salesman Solver:\n";
        cout << "1. Gen random inputs [1..100]\n";
        cout << "2. Brute Force through inputs[1..100]\n\n";
        cout << "0. Exit\n\n";
        cout << "Input: ";
        
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
            bruteForce();
            break;
        }
        }
    } while (op != '0');

    return 0;
}