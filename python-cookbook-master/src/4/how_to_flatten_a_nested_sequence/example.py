#! /usr/bin/env python
# encoding: utf-8

# Example of flattening a nested sequence using subgenerators

# 1. it is Iterable not Iterator
# 2. it is in collections module not in itertools module
from collections import Iterable

def flatten(items, ignore_types=(str, bytes)):
    for x in items:
        # isinstance做类型检查
        if isinstance(x, Iterable) and not isinstance(x, ignore_types):
            # 注意yield from的等价形式
            for i in flatten(x):
                yield i
            # yield from flatten(x)
        else:
            yield x

items = [1, 2, [3, 4, [5, 6], 7], 8]

# Produces 1 2 3 4 5 6 7 8
for x in flatten(items):
    print(x)

items = ['Dave', 'Paula', ['Thomas', 'Lewis']]
for x in flatten(items):
    print(x)
