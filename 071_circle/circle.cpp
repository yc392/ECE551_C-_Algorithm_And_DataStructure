#include "circle.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#include <cmath>
#include <cstdio>

#define pi acos(-1.0)

void Circle::move(double dx, double dy) {
  center.move(dx, dy);
}

double Circle::intersectionArea(const Circle & otherCircle) {
  double diff;
  double d = center.distanceFrom(otherCircle.center);
  if (d >= radius + otherCircle.radius) {
    return 0;
  }

  diff = fabs(radius - otherCircle.radius);
  if (diff >= d) {
    return pi * pow(fmin(radius, otherCircle.radius), 2);
  }

  /* Calculate angles */
  const double a_pow = pow(radius, 2);
  const double b_pow = pow(otherCircle.radius, 2);
  /* Calculate distance */
  const double mid_distance1 = (a_pow - b_pow + pow(d, 2)) / (2 * d);
  const double mid_distance2 = d - mid_distance1;
  const double height = sqrt(pow(radius, 2) - pow(mid_distance1, 2));

  /* Calculate angles */
  const double alpha = std::fmod(std::atan2(height, mid_distance1) * 2.0 + 2 * pi,
                                 2 * pi);  // first circle's central angle
  const double beta = std::fmod(std::atan2(height, mid_distance2) * 2.0 + 2 * pi,
                                2 * pi);  // second circle's central angle

  //  printf("%f and %f\n", alpha, beta);
  /* Calculate areas */
  const double A0 = std::pow(radius, 2) / 2.0 *
                    (alpha - std::sin(alpha));  // Area of the first circula segment
  const double A1 = std::pow(otherCircle.radius, 2) / 2.0 *
                    (beta - std::sin(beta));  // Area of the second circula segment
  return A0 + A1;
}
