#include "vornoi.h"

#include <iostream>

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
      res.push_back(LevelPoint(H3P(x, y, z), type));
    else
      return res;
  }
}


void LevelPoint::dump() const {
  cout << type << ",";
  loc.dump();
  cout << "\n";
}
