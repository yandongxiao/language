#!/usr/bin/env python
# encoding: utf-8

from itertools import chain

A = [1, 2, 3, 4]
B = ["a", "b", "c", "d"]

# chain用于避免对不同的迭代对象调用多次循环操作
# chain 更加节省内存
for x in chain(A, B):
    print x


for i in chain("hello", "world"):
    print i,
print
