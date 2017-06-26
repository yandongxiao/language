#! /usr/bin/env python3
# encoding: utf-8

# 装饰器是一个带参数的装饰器
# 装饰器返回一个修改过的类，为类添加name, shares和price属性
# Stock当中的self.price=price调用就会触发描述符的调用

# Descriptor for a type-checked attribute
class Typed:
    def __init__(self, name, expected_type):
        self.name = name
        self.expected_type = expected_type

    def __get__(self, instance, cls):
        if instance is None:
            return self
        else:
            return instance.__dict__[self.name]

    def __set__(self, instance, value):
        # 为什么不需要判断instance是否为空
        if not isinstance(value, self.expected_type):
            raise TypeError('Expected ' + str(self.expected_type))
        instance.__dict__[self.name] = value

    def __delete__(self, instance):
        del instance.__dict__[self.name]

# Class decorator that applies it to selected attributes
# NOTE: 并不需要特殊的关键字
def typeassert(**kwargs):
    def decorate(cls):
        for name, expected_type in kwargs.items():
            # Attach a Typed descriptor to the class
            setattr(cls, name, Typed(name, expected_type))
        return cls
    return decorate

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
