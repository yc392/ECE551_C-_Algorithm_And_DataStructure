#include "point.h"

class Circle {
 private:
  Point center;
  const double radius;

 public:
  Circle(Point cen, const double rad) : center(cen), radius(rad) {}
  void move(double dx, double dy);
  double intersectionArea(const Circle & otherCircle);
};
