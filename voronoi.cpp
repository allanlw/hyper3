#include "voronoi.h"

#include <iostream>
#include <algorithm>

using namespace std;

vector<LevelPoint> parseLevelPoints(istream &in) {
  vector<LevelPoint> res;
  while (true) {
    double x, y, z;
    string type;

    getline(in, type, ',');
    in >> x;
    in.ignore(1, ',');
    in >> y;
    in.ignore(1, ',');
    in >> z;
    in.ignore(1, '\n');

    if (in.good())
      res.push_back(LevelPoint(x, y, z, type));
    else
      return res;
  }
}

void LevelPoint::dump() const {
  cout << type << ",";
  Hyper3Point::dump();
  cout << "\n";
}

void PointsSet::cull() {
  sort(planes.begin(), planes.end(), [](const PointPlane &x,
       const PointPlane &y) { return x.dist < y.dist; });

  auto &myP = p;

  // Note: C++ standard guarantees the iterator will remain valid over
  // calls to planes.erase if the erased elements are at the end of the
  // container.
  for (auto it = planes.begin(); it != planes.end(); ++it) {
    auto &x = *it;

    planes.erase(remove_if(it + 1, planes.end(), [&myP, &x](PointPlane &y) {
      return !x.plane.onSameSide(myP, y.p);
    }), planes.end());
  }
}

LevelVoronoi::LevelVoronoi(const vector<LevelPoint>& points) {
  for (auto i = points.begin(), e = points.end(); i != e; ++i) {
    PointsSet s(*i);
    for (auto j = points.begin(); j != e; ++j) {
      if (j == i) continue;
      PointPlane pp = {*j, Hyper3Plane::calcMidPlane(s.p, *j), i->distance(*j)};
      s.planes.push_back(pp);
    }
    s.cull();
    this->points.push_back(s);
  }
}

void LevelVoronoi::dump() const {
  cout << points.size() << " points" << endl;

  double pp = 0;
  for (auto i = points.begin(), e = points.end(); i != e; ++i) {
    pp += i->planes.size();
  }
  cout << pp << " planes (" << (pp / points.size()) << "/point)" << endl;
}
