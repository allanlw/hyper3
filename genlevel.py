#!/usr/bin/env python3

import random

subdivisions = 512

X,Y,Z = range(3)

def get_random_inside_cube():
  return tuple(random.random()*2 - 1.0 for i in range(3))

def gen_level():
  points = [get_random_inside_cube() for i in range(subdivisions)]

  type_points = []
  for point in points:
    if point[Z] <= 0:
      type = "ROCK"
    else:
      type = "EMPTY"
    type_points.append((point, type))
  return type_points

def dump_level(level):
  for line in level:
    print("{0},{1},{2},{3}".format(line[1], *line[0]))

if __name__ == "__main__":
  dump_level(gen_level())
