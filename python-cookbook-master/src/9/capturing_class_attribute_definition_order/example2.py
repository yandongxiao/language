#! /usr/bin/env python3
# encoding: utf-8

# Example of a metaclass that rejects duplicate definitions
# 防止类型对象的重定义

from collections import OrderedDict

class NoDupOrderedDict(OrderedDict):
    def __init__(self, clsname):
        self.clsname = clsname
        super().__init__()

    # 类方法的定义过程，其实是在dict内添加一项映射
    # 由于NoDupOrderedDict的本质是一个dict，所以name if self的语法就能理解了
    def __setitem__(self, name, value):
        if name in self:    # 这个
            raise TypeError('{} already defined in {}'.format(name, self.clsname))
        super().__setitem__(name, value)

class OrderedMeta(type):
    def __new__(cls, clsname, bases, clsdict):
        d = dict(clsdict)
        d['_order'] = [name for name in clsdict if name[0] != '_']
        return type.__new__(cls, clsname, bases, d)

    @classmethod
    def __prepare__(cls, clsname, bases):
        return NoDupOrderedDict(clsname)

# Example
class A(metaclass=OrderedMeta):
    def spam(self):
        pass

    print('**** A type error is expected now:')
    def spam(self):
        pass

