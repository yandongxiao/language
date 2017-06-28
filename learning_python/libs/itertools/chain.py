#!/usr/bin/env python
# encoding: utf-8

from itertools import chain

a = [1, 2, 3]
b = [4, 5, 6]

for x in chain(a, b):
    print x,
