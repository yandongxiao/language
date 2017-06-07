#!/usr/bin/env python
# encoding: utf-8

from collections import Iterable

def flat_scan(items):
    for x in items:
        if isinstance(x, Iterable) and not isinstance(x, (bytes, str)):
            for i in flat_scan(x):
                yield i
        else:
            yield x

items = [1, 2, [3, 4, [5, 6], 7], 8]
print list(flat_scan(items))

items = ['Dave', 'Paula', ['Thomas', 'Lewis']]
print list(flat_scan(items))
