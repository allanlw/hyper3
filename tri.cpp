#include "tri.h"

#include <cmath>
#include <cassert>

using namespace std;

HyperPoly HyperPoly::getUniverse() {
  std::vector<HyperTri> tris;

  std::vector<H3P> p;
  for (int i = 0; i < 8; i++) {
    float x = (i & 1) ? INFINITY : -INFINITY;
    float y = (i & 2) ? INFINITY : -INFINITY;
    float z = (i & 4) ? INFINITY : -INFINITY;
    p.push_back(H3P(x, y, z));
  }

#define TRI(a, b, c) tris.push_back(Tri(p[a], p[b], p[c]))

#define FACE(a, b, c, d) do { TRI(a, b, c); TRI(a, c, d); } while (0)

  FACE(0, 1, 3, 2);
  FACE(0, 2, 6, 4);
  FACE(0, 1, 5, 4);

  FACE(7, 6, 4, 5);
  FACE(7, 6, 2, 3);
  FACE(7, 3, 1, 5);

  return HyperPoly(tris);
}

HyperPoly HyperPoly::clip(const Hyper3Plane& plane, const H3P& point) {
  vector<HyperTri> newPoly;
  for (auto &t : tris) {
    auto clips = t.slice(plane, point);
    newPoly.insert(newPoly.end(), clips.begin(), clips.end());
  }
  return HyperPoly(newPoly);
}

vector<HyperTri> HyperTri::slice(const Hyper3Plane& plane, const H3P& ref) const {
  vector<HyperTri> res;
  int countSameSide = 0;
  for (auto &point : points) {
    countSameSide += plane.onSameSide(ref, point);
  }
  switch (countSameSide) {
  case 3: // entirely unclipped
    res.push_back(*this);
    break;
  case 0: // entirely clipped
    break;
  case 2: // one vertex is clipped, return two tris
    for (int i = 0; i < 3; i++) {
      if (plane.onSameSide(ref, points[i])) continue;

      auto newP1 = plane.intersectSegment(points[i], points[(i+1)%3]);
      auto newP2 = plane.intersectSegment(points[i], points[(i+2)%3]);

      vector<H3P> newTri1;
      newTri1.push_back(newP1);
      newTri1.push_back(points[(i+1)%3]);
      newTri1.push_back(newP2);

      vector<H3P> newTri2;
      newTri2.push_back(points[(i+1)%3]);
      newTri2.push_back(points[(i+2)%3]);
      newTri2.push_back(newP2);

      res.push_back(HyperTri(newTri1));
      res.push_back(HyperTri(newTri2));
    }
    break;
  case 1: // two verticies are clipped, return one clipped tri
    for (int i = 0; i < 3; i++) {
      if (!plane.onSameSide(ref, points[i])) continue;

      vector<H3P> newTri;
      newTri.push_back(plane.intersectSegment(points[i], points[(i+1)%3]));
      newTri.push_back(plane.intersectSegment(points[i], points[(i+2)%3]));
      newTri.push_back(points[i]);
      res.push_back(HyperTri(newTri));
      break;
    }
    break;
  default: // ??
    assert(false);
  }

  return res;
}
