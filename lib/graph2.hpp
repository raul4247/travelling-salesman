#ifndef GRAPH2_H
#define GRAPH2_H

#include <list>
#include <vector>
#include <cmath>
using std::vector;

namespace genetic {
    class Graph {
        private:
            vector<vector<double>> *matrix_adj;
            int vertices;
            double default_value = -1;
        public:
            Graph(int vertices);
            ~Graph();
            void display();
            int get_vertices();
            double get_conection(int v1, int v2);
            void add_conection(int v1, int v2, double value);
            void del_conection(int v1, int v2);
    };
}
#endif // GRAPH2_H