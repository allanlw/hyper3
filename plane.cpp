#include "plane.h"

#include <cmath>
#include <cassert>

using namespace std;

Hyper3Plane Hyper3Plane::calcMidPlane(const Hyper3Point& p,
        const Hyper3Point& q) {
  auto _psq = sqrtf(p.oneMinusSquareNorm());
  auto _qsq = sqrtf(q.oneMinusSquareNorm());
  auto a = q * _psq - p * _qsq;
  auto b = _qsq - _psq;
  return Hyper3Plane(a, b);
}

bool Hyper3Plane::onSameSide(const H3P& x, const H3P& y) const {
  float xs = a.dotProduct(x) + b;
  float ys = a.dotProduct(y) + b;

  return xs == 0.0 || ys == 0.0 || signbit(xs) == signbit(ys);
}

H3P Hyper3Plane::intersectSegment(const H3P& x, const H3P& y) const {
  auto t = (a*y + b)/(a*(y - x));
  return x*t + y*(1-t);
}
