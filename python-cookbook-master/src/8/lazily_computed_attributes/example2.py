#!/usr/bin/env python
# encoding: utf-8

import math

def lazyproperty(func):
    name = func.__name__
    # v = property(new_func)
    @property
    def new_func(self):
        if hasattr(self, name):
            return getattr(self, name)
        else:
            value = func(self)
            setattr(self, name, value)
            return value
    return new_func


class Circle:
    def __init__(self, radius):
        self.radius = radius

    # area = lazyproperty(area)
    @lazyproperty
    def area(self):
        print('Computing area')
        return math.pi * self.radius ** 2

    @lazyproperty
    def perimeter(self):
        print('Computing perimeter')
        return 2 * math.pi * self.radius

c = Circle(1)
print(c.area)
print(c.area)

# 为什么这里有perimeter属性
# dir(c)还包括了类的属性，应该使用c.__dict__方法
print(c.__dict__)
