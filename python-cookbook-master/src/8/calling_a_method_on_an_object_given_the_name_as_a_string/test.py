#!/usr/bin/env python
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

p = Point(3, 4)


# use getattr function
print getattr(p, "distance")(0, 0)


from operator import methodcaller
mtd = methodcaller("distance", 0, 0)
print mtd(p)

# Application in sorting
points = [
    Point(1, 2),
    Point(3, 0),
    Point(10, -3),
    Point(-5, -7),
    Point(-1, 8),
    Point(3, 2)
]
mtd = methodcaller("distance", 0, 0)

points.sort(key = lambda p: mtd(p))
for d in points:
    print mtd(d)
