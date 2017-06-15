#!/usr/bin/env python
# encoding: utf-8

class Circle:
    def __init__(self, radius):
        self.radius = radius

    @property
    def area(self):
        return 3.14 * self.radius * self.radius

    @property
    def length(self):
        return 3.14 * 2 * self.radius

c = Circle(5)
print(c.radius)
print(c.area)
print(c.length)
