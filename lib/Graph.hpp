#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include "../lib/Point.hpp"

using namespace std;

namespace TravelingSalesman
{
    class Graph;

    class Graph
    {
    public:
        double **matrix;
        int size;
        int vertexCount;
        vector<Point> points;
        Graph(int);
        ~Graph();
        void addPoint(Point);
    };
}

#endif
