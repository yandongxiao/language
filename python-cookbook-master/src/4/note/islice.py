#!/usr/bin/env python
# encoding: utf-8

# 在迭代器和生成器上使用切片操作
from itertools import islice

def gen():
    i = 0
    while True:
        yield i
        i += 1

g = gen()
for i in islice(g, 10, 20):
    print i,
