#pragma once

#include "constants.h"

struct Point
{
private:
    bool _isEqual(double a, double b) const
    {
        return a - b < eps && b - a < eps;
    }
public:
    double x;
    double y;
    Point(double x = 0, double y = 0): x(x), y(y){}
    bool operator==(const Point& right) const { return (_isEqual(x, right.x) && _isEqual(y, right.y)) ? true : false; }
    bool operator!=(const Point& right) const { return (_isEqual(x, right.x) && _isEqual(y, right.y)) ? false : true; }
};