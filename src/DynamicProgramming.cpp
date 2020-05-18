
#include <bits/stdc++.h>
#include "../lib/Graph.hpp"

using namespace std;
using Graph = TravelingSalesman::Graph;
using Point = TravelingSalesman::Point;

int main(int argc, char *argv[])
{
    fstream inputFile("inputs/vertices_12.in", ios_base::in);

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


    return 0;
}
