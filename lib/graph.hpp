#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include "../lib/point.hpp"

using std::vector;

namespace traveling_salesman
{
    class Graph
    {
        public:
            double **matrix;
            int size;
            int vertex_count;
            vector<Point> points;
            Graph(int);
            ~Graph();
            void add_point(Point);
    };
}

#endif
