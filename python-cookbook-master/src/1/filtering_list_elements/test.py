#!/usr/bin/env python
# encoding: utf-8


mylist = [1, 4, -5, 10, -7, 2, 3, -1]

# All positive values
print [x for x in mylist if x > 0]

# All negative values
print [x for x in mylist if x < 0]

# Negative values clipped to 0
# 必须前置
print [x if x>0 else 0 for x in mylist]

# Positive values clipped to 0
print [x if x<0 else 0 for x in mylist]

# Compressing example

addresses = [
    '5412 N CLARK',
    '5148 N CLARK',
    '5800 E 58TH',
    '2122 N CLARK',
    '5645 N RAVENSWOOD',
    '1060 W ADDISON',
    '4801 N BROADWAY',
    '1039 W GRANVILLE',
]

counts = [ 0, 3, 10, 4, 1, 7, 6, 1]

# compress is a class
from itertools import compress
# more5 = [x if x>5 else 0 for x in counts]
more5 = [ n > 5 for n in counts ]   # 缩写形式, 元素是布尔类型
print list(compress(addresses, more5))

print [y for x,y in zip(counts, addresses) if x > 5 ]
