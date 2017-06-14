#!/usr/bin/env python
# encoding: utf-8

# 如何使用一个函数作为一个装饰器
# 注意如何使用wraps函数来纠正装饰器的__name__属性

from functools import wraps

class sample:
    def __init__(self, counter):
        self.counter = counter

    def __call__(self, fn):
        print self.counter
        @ wraps(fn)
        def infunc():
            print "-----"
            fn()
            print "====="
        return infunc

# 等价与
# s = sample(1)
# hello = s(hello)
@sample(1)
def hello():
    print "hello"

print hello.__name__
hello()
