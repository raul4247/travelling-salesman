#include "../lib/graph.hpp"

namespace traveling_salesman
{
    Graph::Graph(int size)
    {
        this->size = size;
        matrix = new double *[size];
        for (int i = 0; i < size; i++)
        {
            matrix[i] = new double[size];
            matrix[i][i] = 0;
        }
        vertex_count = 0;
    }

    Graph::~Graph()
    {
        for (int i = 0; i < size; ++i)
            delete[] matrix[i];
        delete[] matrix;
    }

    void Graph::add_point(Point p)
    {
        points.push_back(p);

        for (int i = 0; i < vertex_count; i++)
        {
            double dist = p.dist_to(points[i]);
            matrix[i][vertex_count] = matrix[vertex_count][i] = dist;
        }

        vertex_count++;
    }
}
