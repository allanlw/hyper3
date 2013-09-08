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

  std::deque<PointPlane> newPlanes;

  while (planes.size() > 0) {
    auto x = planes.front();
    planes.pop_front();

    newPlanes.push_back(x);

    planes.erase(remove_if(planes.begin(), planes.end(), [&x](PointPlane &y) {
      return !x.plane.onSameSide(x.p, y.p);
    }), planes.end());
  }

  planes = newPlanes;
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
