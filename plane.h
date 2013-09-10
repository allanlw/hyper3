#ifndef _PLANE_H
#define _PLANE_H

#include "point.h"

struct Hyper3Plane {
  Hyper3Point a;
  float b;

  /* This plane represents the solution to ax + b = 0 */

  Hyper3Plane(Hyper3Point a, float b) : a(a), b(b) { }

  static Hyper3Plane calcMidPlane(const Hyper3Point&, const Hyper3Point&);

  /* test if two points are on the same side of the plane.
     if either point is _EXACTLY_ on the plane, then any other point is
     "on the same side" */
  bool onSameSide(const Hyper3Point&, const Hyper3Point&) const;

  H3P intersectSegment(const H3P&, const H3P&) const;
};

#endif
