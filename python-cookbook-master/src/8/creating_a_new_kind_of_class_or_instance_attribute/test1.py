#!/usr/bin/env python3
# encoding: utf-8

class Integer:
    def __init__(self, name):
        self.name = name

    def __get__(self, instance, cls):
        if instance is None:
            return self
        return instance.__dict__[self.name]

    def __set__(self, instance, val):
        if instance is None:
            return
        if not isinstance(val, int):
            raise TypeError("expect int type")
        instance.__dict__[self.name] = val

class Point:
    x = Integer('x')
    y = Integer('y')

    def __init__(self, x, y):
        self.x = x
        self.y = y

p1 = Point(3, 4)
print(p1.x)

p2 = Point(30, 40)
print(p2.x)

try:
    p2.x = "nihao"
except TypeError as e:
    print(e)
