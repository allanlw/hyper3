#ifndef _VERNOI_H
#define _VERNOI_H

#include <string>
#include <istream>
#include <vector>
#include <deque>

#include "point.h"
#include "tri.h"
#include "plane.h"

struct LevelPoint : public Hyper3Point {
  std::string type;

  LevelPoint(float x, float y, float z, std::string type) :
      Hyper3Point(x, y, z), type(type) { }

  void dump() const;
};

std::vector<LevelPoint> parseLevelPoints(std::istream &in);

struct PointPlane {
  LevelPoint p;
  Hyper3Plane plane;
  float dist;
};

struct VoronoiRegion {
  VoronoiRegion(LevelPoint p) : p(p) { }

  LevelPoint p;
  std::deque<PointPlane> planes;

  void cull();

  HyperPoly calcPoly() const;
};

class LevelVoronoi {
public:
  LevelVoronoi(const std::vector<LevelPoint>& points);

  void dump() const;

  std::deque<VoronoiRegion>& getPoints() { return points; }

  std::deque<HyperPoly> calcPolys() const;

private:
  std::deque<VoronoiRegion> points;
};

#endif
