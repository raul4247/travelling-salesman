#ifndef POINT_H
#define POINT_H

#include <utility>
#include <math.h>

using namespace std;

namespace TravelingSalesman
{
    class Point;

    class Point
    {
    private:
        int x, y;

    public:
        Point(int, int);
        int getX();
        int getY();
        pair<int, int> getPair();
        double distTo(Point);
        friend bool operator==(const Point &p1, const Point &p2)
        {
            return (p1.x == p2.x) && (p1.y == p2.y);
        }
    };
}

#endif
