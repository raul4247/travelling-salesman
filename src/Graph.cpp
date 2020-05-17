#include "../lib/Graph.hpp"

using Graph = TravelingSalesman::Graph;

Graph::Graph(int size)
{
    this->size = size;
    matrix = new double *[size];
    for (int i = 0; i < size; i++)
    {
        matrix[i] = new double[size];
        matrix[i][i] = 0;
    }
    vertexCount = 0;
}

Graph::~Graph()
{
    for (int i = 0; i < size; ++i)
        delete[] matrix[i];
    delete[] matrix;
}

void Graph::addPoint(Point p)
{
    points.push_back(p);

    for (int i = 0; i < vertexCount; i++)
    {
        double dist = p.distTo(points[i]);
        matrix[i][vertexCount] = matrix[vertexCount][i] = dist;
    }

    vertexCount++;
}
