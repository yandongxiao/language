#!/usr/bin/env python3
# encoding: utf-8

class Proxy:
    def __init__(self, obj):
        self._obj = obj

    def __getattr__(self, name):
        # 下面两行没有存在的必要性, 因为下划线开头的属性根本不会触发__getattr__的调用
        # if name.startswith("_"):
        #    return self.name
        return getattr(self._obj, name)

    def __setattr__(self, name, val):
        if name.startswith("_"):
            super().__setattr__(name, val)
        else:
            setattr(self._obj, name, val)

class sample:
    def __init__(self, cnt):
        self.cnt = cnt
    def func(self):
        print(self.cnt)

s = sample(10)
p = Proxy(s)
assert s.cnt == 10

p.cnt = 20
assert p.cnt == 20
#assert s.cnt == 20

p.name = "jack"
assert p.name == "jack"
#assert s.name == "jack"

p._age = 10         # NOTE: 不但_age和_obj赋值操作都触发了__setattr__函数的调用
assert p._age == 10 # NOTE: 如果是以下划线开头，则不会调用__getattr__函数

try:
    print(s._age)
except AttributeError as e:
    print(e)

try:
    print(p.nosuch)
except AttributeError as e:
    print(e)
