#!/usr/bin/env python
# encoding: utf-8

class D(object):
    def __init__(self, f):
        self.f = f
        self.__name__ = f.__name__
        self.__doc__ = f.__doc__
    def __call__(self, *args, **kwargs):
        print("class")
        self.f(*args, **kwargs)
        pass

@D
def hello(a, b, c):
    print("hello", a, b, c)

hello(1,2,3)
print hello.__name__
