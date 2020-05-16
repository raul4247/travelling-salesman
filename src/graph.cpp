#include "../lib/graph.hpp"
#include <iostream>

Graph::Graph(int vertices){
    this->vertices = vertices;
    this->matrix_adj = new vector<vector<int>>(vertices,vector<int>(vertices, this->default_value));
}

Graph::~Graph(){
    delete matrix_adj;
    matrix_adj = nullptr;
}

void Graph::display(){
    for (auto& line : *matrix_adj){
        for (auto v : line){
            cout << v << " ";
        }
        cout << endl;
    }
}

void Graph::add_conection(int v1, int v2, int value){
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

int Graph::get_conection(int v1, int v2){
    return this->matrix_adj->at(v1).at(v2);
}