#! /usr/bin/python
# encoding: utf-8

# 命名元组的核心作用是解决以下表区分不同对象所带来的问题

from collections import namedtuple
# namedtuple函数返回Python中标准元组类型子类的一个工厂方法
Stock = namedtuple('Stock', ['name', 'shares', 'price'])

def compute_cost(records):
    total = 0.0
    for rec in records:
        # 实例化
        s = Stock(*rec)     # the parameter is a tuple.
        # 尽管它看起来像是一个类实例，但是它跟元组类型是可交换的
        # 不像字典那样，一个命名元组是不可更改的
        # 更改方法如下s = s._replace(price=75)
        # _, shares, price = s
        # total += shares * price
        total += s.shares * s.price
    return total

# Some Data
records = [
    ('GOOG', 100, 490.1),
    ('ACME', 100, 123.45),
    ('IBM', 50, 91.15)
]

print(compute_cost(records))
