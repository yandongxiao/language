#!/usr/bin/env python3

"""
A demonstration of classes and their special methods in Python.
"""

class Vec:
    """A simple vector class.

    Instances of the Vec class can be constructed from numbers

    >>> a = Vec(1, 2, 3)
    >>> b = Vec(3, 2, 1)

    added
    >>> a + b
    Vec(4, 4, 4)

    subtracted
    >>> a - b
    Vec(-2, 0, 2)

    and multiplied by a scalar on the left
    >>> 3.0 * a
    Vec(3.0, 6.0, 9.0)

    or on the right
    >>> a * 3.0
    Vec(3.0, 6.0, 9.0)
    """
    def __init__(self, *v): 			#当我们不清楚还有多少个元素时，就用*args代替. 注意是元组类型.
        self.v = list(v)				#不需要return，在__init__函数调用之前，已经有了实例对象了.

    @classmethod						#定义了一个类方法，所以cls就是Vec类对象.
    def fromlist(cls, v):
        if not isinstance(v, list):
            raise TypeError
        inst = cls()					#难道这是默认构造方法,非也，这是因为__init__(slef, *v), *v表示零个或多个.
        inst.v = v
        return inst						#作用是返回一个Vec实例的对象,还有这个功能.

    def __repr__(self):
        args = ', '.join(repr(x) for x in self.v)
        return 'VEC : Vec : Vec({})'.format(args)

    def __len__(self):
        return len(self.v)

    def __getitem__(self, i):
        return self.v[i]

    def __add__(self, other):
        # Element-wise addition
        v = [x + y for x, y in zip(self.v, other.v)]
        return Vec.fromlist(v)

    def __sub__(self, other):
        # Element-wise subtraction
        v = [x - y for x, y in zip(self.v, other.v)]
        return Vec.fromlist(v)

    def __mul__(self, scalar):
        # Multiply by scalar
        v = [x * scalar for x in self.v]
        return Vec.fromlist(v)

    __rmul__ = __mul__

aaa=Vec(1)
#help(Vec.__repr__)
print (aaa)
print (len(aaa))
