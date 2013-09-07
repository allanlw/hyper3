#include "voronoi.h"

using namespace std;

vector<LevelPoint> parseLevelPoints(istream &in) {
  vector<LevelPoint> res;
  while (in.good()) {
    double x, y, z;
    string type;
    in >> type;
    in >> x >> y >> z;
    res.push_back(LevelPoint(H3P(x, y, z), type));
  }
  return res;
}

