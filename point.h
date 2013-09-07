#ifndef _POINT_H
#define _POINT_H

struct Hyper3Point {
  Hyper3Point(double x, double y, double z) : x(x), y(y), z(z) { }

  double x;
  double y;
  double z;

  void dump() const;
};

typedef Hyper3Point H3P;

#endif
