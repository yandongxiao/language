#!/usr/bin/env python
# encoding: utf-8

# 继承object的__new__方法
# 若你没有在Foo类中没有写__new__方法，Foo实例化是自动调用父类__new__方法，
# 这个方法返回值为类的实例(self)
# def __new__(cls, *agrs, **kwds)   貌似后面两个参数没有什么作用
class sample(object):
    # NOTE: __init__ 被调用是实例已经被创建了出来
    def __init__(self):
        print "__init__"

    def __new__(cls):
        print "__new__"
        return object.__new__(cls)

s = sample()
