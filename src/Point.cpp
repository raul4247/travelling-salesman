#include "../lib/Point.hpp"

using Point = TravelingSalesman::Point;

Point::Point(int x, int y)
{
    this->x = x;
    this->y = y;
}

int Point::getX()
{
    return x;
}

int Point::getY()
{
    return y;
}

pair<int, int> Point::getPair()
{
    return make_pair(x, y);
}

double Point::distTo(Point p)
{
    return sqrt(pow(x - p.getX(), 2) + pow(y - p.getY(), 2));
}
