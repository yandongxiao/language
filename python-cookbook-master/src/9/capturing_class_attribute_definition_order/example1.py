#! /usr/bin/env python3
# encoding: utf-8

# Example of capturing class definition order

from collections import OrderedDict

# A set of descriptors for various types
class Typed:
    _expected_type = type(None)
    def __init__(self, name=None):
        self._name = name

    def __set__(self, instance, value):
        print("third")
        if not isinstance(value, self._expected_type):
            raise TypeError('Expected ' +str(self._expected_type))
        instance.__dict__[self._name] = value

class Integer(Typed):
    _expected_type = int

class Float(Typed):
    _expected_type = float

class String(Typed):
    _expected_type = str


# Metaclass that uses an OrderedDict for class body
# 继承自type的元类OrderedMeta
# bases: 表明了类对象的基类
# clsdict 是类对象的属性
class OrderedMeta(type):        # 继承于type
    # __new__方法用来创建一个类对象
    def __new__(cls, clsname, bases, clsdict):
        print("second", clsname)
        d = dict(clsdict)   # 传递进来的clsdict是一个OrderedDict实例对象，所以要该
        order = []
        for name, value in clsdict.items():
            if isinstance(value, Typed):
                value._name = name
                order.append(name)
        d['_order'] = order
        return type.__new__(cls, clsname, bases, d)

    # 对比__new__的参数可知，返回的是clsdict
    @classmethod
    def __prepare__(cls, clsname, bases):
        print("first", clsname)
        return OrderedDict()


# Example class that uses the definition order to initialize members
# Structure['_order'] 的值为空
class Structure(metaclass=OrderedMeta):
    def as_csv(self):
        return ','.join(str(getattr(self, name)) for name in self._order)


# Example use
# Stock['_order'] = ['name', 'shares', 'price']
class Stock(Structure):
    name = String()
    shares = Integer()
    price = Float()
    def __init__(self, name, shares, price):
        self.name = name
        self.shares = shares
        self.price = price


if __name__ == '__main__':
    s = Stock('GOOG',100,490.1)
    print(s.name)
    print(s.as_csv())
    try:
        t = Stock('AAPL','a lot', 610.23)
    except TypeError as e:
        print(e)

