#!/usr/bin/env python
# encoding: utf-8

# Some Data
records = [
    ('GOOG', 100, 490.1),
    ('ACME', 100, 123.45),
    ('IBM', 50, 91.15)
]

# method - 1
total = 0
for elmt in records:
    total += elmt[1] * elmt[2]
print total


# method - 2
# namedtuple 是一个meta class, 创建了一个class
from collections import namedtuple
Good = namedtuple("GOOD", ['name', 'num', 'price'])
total = 0
for elmt in records:
    good = Good(*elmt)
    total += good.price * good.num
print total
