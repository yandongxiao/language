#! /usr/bin/python
# encoding: utf-8

# Example of using partial() with sorting a list of (x,y) coordinates
# 很多时候 partial() 能实现的效果，lambda表达式也能实现。
from functools import partial

points = [(7,7), (1, 2), (3, 4), (5, 6), (7, 7) ]

import math
def distance(p1, p2):
    x1, y1 = p1
    x2, y2 = p2
    return math.hypot(x2 - x1, y2 - y1)

pt = (4,3)
points.sort(key=partial(distance, pt))
print(points)
