#include "point.h"

#include <cmath>
#include <cstdio>

void Point::move(double dx, double dy) {
  x += dx;
  y += dy;
}

double Point::distanceFrom(const Point & p) {
  double distance;
  distance = sqrt(pow(x - p.x, 2) + pow(y - p.y, 2));
  return distance;
}
