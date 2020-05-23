#include "../lib/point.hpp"

using std::make_pair;
namespace traveling_salesman
{
    Point::Point(int x, int y)
    {
        this->x = x;
        this->y = y;
    }

    int Point::get_x()
    {
        return this->x;
    }

    int Point::get_y()
    {
        return this->y;
    }

    pair<int, int> Point::get_pair()
    {
        return make_pair(x, y);
    }

    double Point::dist_to(Point p)
    {
        return sqrt(pow(x - p.get_x(), 2) + pow(y - p.get_y(), 2));
    }
}
