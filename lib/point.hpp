#ifndef POINT_H
#define POINT_H

#include <utility>
#include <math.h>

using std::pair;

namespace traveling_salesman
{
    class Point
    {
        private:
            // Id usado no algoritmo genetico para identificar uma cidade da outra
            int id;
            // Armazena as coordenadas x e y do ponto.
            pair<int, int> coordinates;

        public:
            Point(int id, int x, int y);
            Point(int x, int y)
            {
                this->id = 0;
                this->coordinates.first = x;
                this->coordinates.second = y;
            }
            int get_id();
            int get_x();
            int get_y();
            pair<int, int> get_pair();
            double dist_to(Point);
            friend bool operator==(const Point &p1, const Point &p2)
            {
                return (p1.id == p2.id) && (p1.coordinates == p2.coordinates);
            }
    };
}

#endif
