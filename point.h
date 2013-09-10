#ifndef _POINT_H
#define _POINT_H

struct Hyper3Point {
  float x;
  float y;
  float z;

  Hyper3Point(float x, float y, float z) : x(x), y(y), z(z) { }

  virtual void dump() const;

  float distance(const Hyper3Point&) const;

  float dotProduct(const Hyper3Point&) const;

  float norm() const;

  float oneMinusSquareNorm() const;

  Hyper3Point operator*(float) const;
  float operator*(const Hyper3Point&) const;
  Hyper3Point operator+(const Hyper3Point&) const;
  Hyper3Point operator-(const Hyper3Point&) const;
};

typedef Hyper3Point H3P;

#endif
