#include <list>
#include <vector>
#include <cmath>
using namespace std;

class Graph {
    private:
        vector<vector<int>> *matrix_adj;
        int vertices;
        int default_value = -1;
    public:
        Graph(int vertices);
        ~Graph();
        void display();
        int get_vertices();
        int get_conection(int v1, int v2);
        void add_conection(int v1, int v2, int value);
        void del_conection(int v1, int v2);
};
