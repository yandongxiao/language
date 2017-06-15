#!/usr/bin/env python
# encoding: utf-8

# property 装饰器的作用
# 使得一个函数的访问方式变成接口形式

import math
class Circle:
    def __init__(self, radius):
        self.radius = radius

    @property
    def area(self):
        return math.pi * self.radius ** 2

    @property
    def diameter(self):
        return self.radius ** 2

    @property
    def perimeter(self):
        return 2 * math.pi * self.radius

c = Circle(4.0)
print c.area
print c.diameter
print c.perimeter
