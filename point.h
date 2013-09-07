#ifndef _POINT_H
#define _POINT_H

struct Hyper3Point {
public:
  Hyper3Point(double x, double y, double z) : x(x), y(y), z(z) { }

  double x;
  double y;
  double z;
};

typedef Hyper3Point H3P;

#endif
