#include "../lib/point.hpp"

using std::make_pair;
namespace traveling_salesman
{
    Point::Point(int id, int x, int y){
        this->id = id;
        this->coordinates.first = x;
        this->coordinates.second = y;
    }

    int Point::get_id()
    {
        return this->id;
    }

    int Point::get_x()
    {
        return this->coordinates.first;
    }

    int Point::get_y()
    {
        return this->coordinates.second;
    }

    pair<int, int> Point::get_pair()
    {
        return this->coordinates;
    }

    double Point::dist_to(Point p)
    {
        return sqrt(pow(p.get_x() - this->get_x(), 2) + pow(p.get_y() - this->get_y(), 2));
    }
}
