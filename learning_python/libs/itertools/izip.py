#!/usr/bin/env python
# encoding: utf-8

a = [1,2,3,4,5]
b = [-1,-2,-3,4,5]

from itertools import izip
for i, j in izip(a, b):
    print i, j,
