#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include "../lib/Point.hpp"

namespace TravelingSalesman
{
    class Graph
    {
    public:
        double **matrix;
        int size;
        int vertexCount;
        std::vector<Point> points;
        Graph(int);
        ~Graph();
        void addPoint(Point);
    };
}

#endif
