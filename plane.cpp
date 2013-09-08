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
#if 0
H3P Hyper3Plane::intersectSegment(const H3P& x, const H3P& y) const {
  assert(!onSameSide(x, y));


  /*
  <a c> + b == 0

  a[0] * c[0] + a[1] * c[1] + a[2] * c[2] + b == 0

  points are on the line if they satisfy the equation:
    tx + (1-t)y = p for t in 0..1

  c = tx + (1-t)y
  <a c> + b == 0
  */

}
#endif
