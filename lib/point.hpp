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
            int x, y;

        public:
            Point(int, int);
            int get_x();
            int get_y();
            pair<int, int> get_pair();
            double dist_to(Point);
            friend bool operator==(const Point &p1, const Point &p2)
            {
                return (p1.x == p2.x) && (p1.y == p2.y);
            }
    };
}

#endif
