#include "../lib/graph.hpp"

namespace traveling_salesman
{
    Graph::Graph(int size)
    {
        this->size = size;
        this->matrix = new vector<vector<double>>(size, vector<double>(size, default_value));
        vertex_count = 0;
    }

    Graph::~Graph()
    {
        delete this->matrix;
        this->matrix = nullptr;
    }

    void Graph::add_point(Point p)
    {
        points.push_back(p);

        for (int i = 0; i < vertex_count; i++)
        {
            double dist = p.dist_to(points[i]);
            this->set_conection(i, vertex_count, dist);
        }

        vertex_count++;
    }

    void Graph::set_conection(int v1, int v2, double value){
        if(v1 < this->size && v2 < this->size){
            this->matrix->at(v1).at(v2) = value;
            this->matrix->at(v2).at(v1) = value;
        }
    }

    void Graph::del_conection(int v1, int v2){
        if (v1 < this->size && v2 < this->size){
            this->matrix->at(v1).at(v2) = this->default_value;
            this->matrix->at(v2).at(v1) = this->default_value;
        }
    }

    double Graph::get_conection(int v1, int v2){
        return this->matrix->at(v1).at(v2);
    }

}
