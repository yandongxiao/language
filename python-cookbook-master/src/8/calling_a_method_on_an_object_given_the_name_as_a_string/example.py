#! /usr/bin/env python
# encoding: utf-8

# Example of calling methods by name

import math
class Point:
    def __init__(self, x, y):
        self.x = x
        self.y = y

    def __repr__(self):
        return 'Point({!r:},{!r:})'.format(self.x, self.y)

    def distance(self, x, y):
        return math.hypot(self.x - x, self.y - y)

    def __eq__(self, p):
        if self.x == p.x and self.y == p.y:
            return True
        return False


p = Point(2,3)

# Method 1 : Use getattr
d = getattr(p, 'distance')(0, 0)     # Calls p.distance(0, 0)
print(d)

# Method 2: Use methodcaller
import operator
import copy
points = [
    Point(1, 2),
    Point(3, 0),
    Point(10, -3),
    Point(-5, -7),
    Point(-1, 8),
    Point(3, 2)
]
new_points = copy.deepcopy(points)

d = operator.methodcaller('distance', 0, 0)(p)
print(d)
points.sort(key=operator.methodcaller('distance', 0, 0))

from functools import partial
distance = partial(Point.distance, x=0, y=0)
new_points.sort(key=lambda x: distance(x))
assert points == new_points
