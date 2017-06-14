#!/usr/bin/env python3
# encoding: utf-8

class Typed:
    def __init__(self, key, type):
        self.key = key
        self.type = type

    def __get__(self, instance, cls):
        if instance is None:
            return self
        return instance.__dict__[self.key]

    def __set__(self, instance, val):
        if instance is None:
            return self

        if not isinstance(val, self.type):
            raise TypeError("expect type " + str(self.type))

        instance.__dict__[self.key] = val

    def __delete__(self, instance):
        print("__del__")
        del instance.__dict__[self.key]

def typeassert(**kvparis):
    def dec(cls):
        for k, v in kvparis.items():
            setattr(cls, k, Typed(k, v))
        return cls
    return dec

# Example use
# dec = typeassert(name=str, shares=int, price=float)
# Stock = dec(Stock)
@typeassert(name=str, shares=int, price=float)
class Stock:
    def __init__(self, name, shares, price):
        self.name = name
        self.shares = shares
        self.price = price

if __name__ == '__main__':
    s = Stock('ACME', 100, 490.1)
    print(s.name, s.shares, s.price)
    s.shares = 50
    try:
        s.shares = 'a lot'
    except TypeError as e:
        print(e)

    del s.name
    del s # 并不会触发__delete__的执行
