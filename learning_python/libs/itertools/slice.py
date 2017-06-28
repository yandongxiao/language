#!/usr/bin/env python
# encoding: utf-8

a = [1,2,3,4,5]
b = a[3:]
print b[0]
b[0] = 100
print a[3]

d = {"name":"jack", "age":10, "high": 1.76}
from itertools import islice

for k in islice(d, 2):
    print k


