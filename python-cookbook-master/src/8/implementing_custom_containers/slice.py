#!/usr/bin/env python
# encoding: utf-8

a = [1,2,3]
b = a[:]
b[0] == 100
assert a[0] == 1
