#!/usr/bin/env python
# encoding: utf-8

# A proxy class that wraps around another object, but
# exposes its public attributes

class Proxy:
    def __init__(self, obj):
        self._obj = obj

    def __getattr__(self, key):
        # NOTE: 为什么不用处理以划线开头的成员属性
        print "__getattr__"
        return getattr(self._obj, key)

    def __setattr__(self, key, val):
        print "__setattr__"
        if key.startswith("_"):
            #return setattr(self, key, val)
            # NOTE: 为什么要使用super呢
            super().__setattr__(key, val)
        return setattr(self._obj, key, val)

    def __delattr__(self, key):
        print "__delattr__"
        if key.startswith("_"):
            #return delattr(self, key)
            return super().__delattr__(key)
        return delattr(self._obj, key)

class sample:
    def __init__(self, name):
        self.name = name

s = sample("tom")
s._age = 10
print s._age
del s._age


s.age = 10
print s.age
del s.age
