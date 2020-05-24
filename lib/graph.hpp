#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include "../lib/point.hpp"

using std::vector;
namespace traveling_salesman
{
    class Graph
    {
        private:
            vector<vector<double>> *matrix;
            int size;
            double default_value = 0.0;
            int vertex_count;
        public:
            vector<Point> points;
            Graph(int size);
            ~Graph();
            int get_size();
            double get_conection(int v1, int v2);
            void set_conection(int v1, int v2, double value);
            void del_conection(int v1, int v2);
            void add_point(Point);
    };
}

#endif
