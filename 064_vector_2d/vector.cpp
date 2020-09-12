#include "vector.hpp"

#include <cmath>
#include <cstdio>

/* write your class implementation in this file
 */
void Vector2D::initVector(double init_x, double init_y) {
  xCord = init_x;
  yCord = init_y;
}

double Vector2D::getMagnitude() const {
  double mag = std::sqrt(pow(xCord, 2) + pow(yCord, 2));
  return mag;
}
Vector2D Vector2D::operator+(const Vector2D & rhs) const {
  Vector2D ans;
  ans.xCord = xCord + rhs.xCord;
  ans.yCord = yCord + rhs.yCord;
  return ans;
}

Vector2D & Vector2D::operator+=(const Vector2D & rhs) {
  xCord += rhs.xCord;
  yCord += rhs.yCord;
  return *this;
}
double Vector2D::dot(const Vector2D & rhs) const {
  double ans = xCord * rhs.xCord + yCord * rhs.yCord;
  return ans;
}

void Vector2D::print() const {
  printf("<%.2f, %.2f>", xCord, yCord);
}
