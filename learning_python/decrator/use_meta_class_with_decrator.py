#!/usr/bin/env python
# encoding: utf-8

import types

def decrator(f):
    def newf(*args, **kwargs):
        print("decrator")
        f(*args, **kwargs)
        newf.__name__ = f.__name__
        newf.__doc__ = f.__doc__
    return newf


def decrator_class(future_class_name, future_class_parents, future_class_attr):
    for key in future_class_attr:
        if not key.startswith('__') \
            and type(future_class_attr[key]) is types.FunctionType:
            future_class_attr[key] = decrator(future_class_attr[key])
    return type(future_class_name, future_class_parents, future_class_attr)

__metaclass__ = decrator_class

class Sub1():
    def hello(self):
        print("hello")

s = Sub1()
s.hello()
print s.hello.__name__
