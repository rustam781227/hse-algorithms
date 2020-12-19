#pragma once
#include "rectangle.h"
#include "circle.h"

class Square : public Rectangle
{
public:
    Square(const Point& a, const Point& c) : Rectangle(a, c, 1) {}
    Circle circumscribedCircle() const; // описанна€ окружность
    Circle inscribedCircle() const;
};
