
#include "Point.h"
#include <cmath>

Kaironetic::Draw2D::Point::Point(float x, float y) : x(x), y(y) {}

/// Calculate the distance between two points (in millimeters) using the distance formula
float Kaironetic::Draw2D::Point::distanceTo(Kaironetic::Draw2D::Point input) const {
    return sqrt(pow(this->x - input.x, 2) +
                pow(this->y - input.y, 2) * 1.0);
}


