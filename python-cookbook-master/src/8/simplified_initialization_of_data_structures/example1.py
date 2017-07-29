#! /usr/bin/env python3
# encoding: utf-8

# 如果有大量的类对象作为一个数据结构使用，即这些类对象只有一个__init__方法，
# 可以尝试使用下面的方法进行整合

import math

class Structure:
    # Class variable that specifies expected fields
    _fields= []
    def __init__(self, *args):
        if len(args) != len(self._fields):
            raise TypeError('Expected {} arguments'.format(len(self._fields)))

        # Set the arguments
        for name, value in zip(self._fields, args):
            setattr(self, name, value)

# Example class definitions
if __name__ == '__main__':
    class Stock(Structure):
        _fields = ['name', 'shares', 'price']

    class Point(Structure):
        _fields = ['x','y']

    class Circle(Structure):
        _fields = ['radius']
        def area(self):
            return math.pi * self.radius ** 2

if __name__ == '__main__':
    s = Stock('ACME', 50, 91.1)
    print(s.name, s.shares, s.price)

    p = Point(2,3)
    print(p.x, p.y)

    c = Circle(4.5)
    print(c.radius)

    try:
        s2 = Stock('ACME', 50)
    except TypeError as e:
        print(e)
