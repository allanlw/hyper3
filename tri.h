#ifndef _TRI_H
#define _TRI_H

#include <vector>

#include "point.h"
#include "plane.h"

struct HyperTri {
  H3P points[3];

  HyperTri(H3P a, H3P b, H3P c) : points({a, b, c}) { }
  HyperTri(const std::vector<H3P>& v) : points({ v[0], v[1], v[2] }) { }

  std::vector<HyperTri> slice(const Hyper3Plane&, const H3P&) const;
};

typedef HyperTri Tri;

class HyperPoly {
private:
  std::vector<HyperTri> tris;

public:
  HyperPoly(std::vector<HyperTri>& t) : tris(t) { }

  std::vector<HyperTri>& getTris() { return tris; }
  const std::vector<HyperTri>& getTris() const { return tris; }

  static HyperPoly getUniverse();

  HyperPoly clip(const Hyper3Plane&, const H3P&);
};

#endif
