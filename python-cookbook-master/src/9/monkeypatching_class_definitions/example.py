#! /usr/bin/env python3
# encoding: utf-8

import functools

# 不需要进行wrpas操作，因为还是返回了原先的类对象
# 只是修改了一个属性而已
def log_getattribute(cls):
    # Get the original implementation
    orig_getattribute = cls.__getattribute__

    # Make a new definition
    def new_getattribute(self, name):
        print('getting:', name)
        return orig_getattribute(self, name)

    # Attach to the class and return
    cls.__getattribute__ = new_getattribute
    return cls


def wrapper(func):
    @functools.wraps(func)
    def print_func(*argv, **kwargv):
        print(func.__name__)
        return func(*argv, **kwargv)
    return print_func

# Example use
@log_getattribute
class A:
    # __init__ = wrapper(__init__)
    @wrapper
    def __init__(self,x):
        self.x = x

    def spam(self):
        pass

if __name__ == '__main__':
    a = A(42)
    print(a.x)
    a.spam()
