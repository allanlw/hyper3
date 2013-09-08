#ifndef _VERNOI_H
#define _VERNOI_H

#include <string>
#include <istream>
#include <vector>

#include "point.h"

struct LevelPoint {
  Hyper3Point loc;
  std::string type;

  LevelPoint(H3P loc, std::string type) : loc(loc), type(type) { }

  void dump() const;
};

std::vector<LevelPoint> parseLevelPoints(std::istream &in);

#endif
