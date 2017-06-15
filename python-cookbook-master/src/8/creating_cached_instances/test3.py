#!/usr/bin/env python3
# encoding: utf-8

import weakref

class sample(object):
    _wvd = weakref.WeakValueDictionary()

    def __new__(cls, name):     # 与__init__的参数保持一致
        if name not in cls._wvd:    # 必须使用类型对象cls，来访问_wvd
            s = super().__new__(cls)    # python3的特性
            cls._wvd[name] = s
        else:
            s = cls._wvd[name]
        return s

    def __init__(self, name):
        self.name = name


s1 = sample("foo")
s2 = sample("foo")
assert s1 is s2
