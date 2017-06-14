#!/usr/bin/env python
# encoding: utf-8

# __getattribute__方法会优先__getattr__调用，且调用任何实例属性和方法都会调用__getattribute__
# __getattr__只作用于不存在的属性
class Y(object):
    def __init__(self):
        self.a = 10

    def __getattr__(self, name):
        return name

y = Y()
print y.a
print y.b
print getattr(y, "a")
print getattr(y, "b")
