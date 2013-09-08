#include "voronoi.h"

#include <iostream>

using namespace std;

int main(int argc, char **argv) {
  auto points = parseLevelPoints(cin);
  cout << points.size();
  for (auto &p : points) {
    p.dump();
  }
  cout << endl;

  LevelVoronoi vor(points);

  vor.dump();
  return 0;
}
