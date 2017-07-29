#! /usr/bin/env python3
# encoding: utf-8

import operator

class StructTupleMeta(type):
    # __init__ 调用时类对象已经被创建
    # 注意__init__的第一个参数已经是cls了
    def __init__(cls, *args, **kwargs):
        super().__init__(*args, **kwargs)
        for n, name in enumerate(cls._fields_):
            setattr(cls, name, property(operator.itemgetter(n)))


class StructTuple(tuple, metaclass=StructTupleMeta):
    _fields_ = []   # 之所以需要是因为StructTupleMeta在__init__时需要
    def __new__(cls, *args):
        if len(args) != len(cls._fields_):
            raise ValueError('{} arguments required'.format(len(cls._fields_)))
        return super().__new__(cls,args)


# Examples
class Stock(StructTuple):
    _fields_ = ['name', 'shares', 'price']

class Point(StructTuple):
    _fields_ = ['x', 'y']

if __name__ == '__main__':
    s = Stock('ACME', 50, 91.1)
    print(s)
    print(s[0])
    print(s.name)
    print(s.shares * s.price)
    try:
        s.shares = 23
    except AttributeError as e:
        print(e)
