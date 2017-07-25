#!/usr/bin/env python
# encoding: utf-8

A = [1, 2, 3, 4]
B = ["a", "b", "c", "d"]

# python3当中重命名为zip_longest
from itertools import izip_longest

for a, b in izip_longest(A, B):
    print a, b
