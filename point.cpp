#include "point.h"

#include <iostream>
#include <cmath>

using namespace std;

void Hyper3Point::dump() const {
  cout << x << "," << y << "," << z;
}

static float arccosh(float x) {
  return logf(x + sqrtf(x * x - 1.0));
}

float Hyper3Point::oneMinusSquareNorm() const {
  auto n = norm();
  return 1.0 - n*n;
}

float Hyper3Point::distance(const Hyper3Point& other) const {
  float numerator = 1.0 - dotProduct(other);
  float denominator = oneMinusSquareNorm() * other.oneMinusSquareNorm();
  return arccosh(numerator / sqrtf(denominator));
}

float Hyper3Point::dotProduct(const Hyper3Point& other) const {
  return x * other.x + y * other.y + z * other.z;
}

float Hyper3Point::norm() const {
  return sqrtf(x * x + y * y + z * z);
//  return sqrtf(dotProduct(*this));
}

Hyper3Point Hyper3Point::operator*(float c) const {
  return Hyper3Point(x * c, y * c, z * c);
}

Hyper3Point Hyper3Point::operator-(const Hyper3Point& other) const {
  return Hyper3Point(x - other.x, y - other.y, z - other.z);
}
