#! /usr/bin/env python3
# encoding: utf-8

import time
from functools import wraps

# A simple decorator
def timethis(func):
    @wraps(func)
    def wrapper(*args, **kwargs):
        start = time.time()
        r = func(*args, **kwargs)
        end = time.time()
        print(end-start)
        return r
    return wrapper


# Class illustrating application of the decorator to different kinds of methods
# 由于装饰器timethis是一个通用接口的函数，所以可以应用到所有的方法
class Spam:
    @timethis
    def instance_method(self, n):
        print(self, n)
        while n > 0:
            n -= 1

    @classmethod
    @timethis
    def class_method(cls, n):
        print(cls, n)
        while n > 0:
            n -= 1

    @staticmethod
    @timethis
    def static_method(n):
        print(n)
        while n > 0:
            n -= 1

if __name__ == '__main__':
    s = Spam()
    s.instance_method(10000000)
    Spam.class_method(10000000)
    Spam.static_method(10000000)
