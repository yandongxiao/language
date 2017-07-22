#!/usr/bin/env python
# encoding: utf-8

def add(a, b):
    return a + b


nums = [1, 2]
print add(*nums)

nums = (10, 20)
print add(*nums)

nums = "12"     # 有误
print add(*nums)
