#! /usr/bin/env python
# encoding: utf-8

import math
class Point:
    def __init__(self, x, y):
        self.x = x
        self.y = y
    def __repr__(self):
        return 'Point({!r:},{!r:})'.format(self.x, self.y)
    def distance(self, x, y):
        return math.hypot(self.x - x, self.y - y)

# Application in sorting
points = [
    Point(1, 2),
    Point(3, 0),
    Point(10, -3),
    Point(-5, -7),
    Point(-1, 8),
    Point(3, 2),
    Point(0, 0)
]

# 按照距离Points(0, 0)的远近进行排序
from operator import methodcaller

distance = methodcaller("distance", 0, 0)
points.sort(key=lambda p: distance(p))
for p in points:
    print p.x, p.y
