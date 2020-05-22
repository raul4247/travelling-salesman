#include "../lib/graph.hpp"
#include <iostream>

using std::cout;
using std::endl;

namespace graph {

    Graph::Graph(int vertices){
        this->vertices = vertices;
        this->matrix_adj = new vector<vector<double>>(vertices,vector<double>(vertices, this->default_value));
    }

    Graph::~Graph(){
        delete this->matrix_adj;
        this->matrix_adj = nullptr;
    }

    void Graph::display(){
        for (auto& line : *matrix_adj){
            for (auto v : line){
                cout << v << " ";
            }
            cout << endl;
        }
    }

    void Graph::add_conection(int v1, int v2, double value){
        if(v1 < this->vertices && v2 < this->vertices){
            this->matrix_adj->at(v1).at(v2) = value;
            this->matrix_adj->at(v2).at(v1) = value;
        }
    }

    void Graph::del_conection(int v1, int v2){
        if (v1 < this->vertices && v2 < this->vertices){
            this->matrix_adj->at(v1).at(v2) = this->default_value;
            this->matrix_adj->at(v2).at(v1) = this->default_value;
        }
    }

    double Graph::get_conection(int v1, int v2){
        return this->matrix_adj->at(v1).at(v2);
    }

    int Graph::get_vertices(){
        return this->vertices;
    }
}
