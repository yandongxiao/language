#!/usr/bin/env python
# encoding: utf-8


points = [(7,7), (1, 2), (3, 4), (5, 6), (7, 7) ]

import math
def distance(p1, p2):
    x1, y1 = p1
    x2, y2 = p2
    return math.hypot(x2 - x1, y2 - y1)

print distance(points[0], points[1])


# method-1
def distance2(p2):
    base = (4,3)
    return distance(p2, base)
#points.sort(key=lambda y: distance2(y))

# method-2
from functools import partial
#distance2 = partial(distance, p2=(4,3))
#points.sort(key=lambda y: distance2(y))
points.sort(key=partial(distance, p2=(4,3)))    # 不需要借助lambda
print points
