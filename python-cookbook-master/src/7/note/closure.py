#!/usr/bin/env python
# encoding: utf-8

# 如果一个类只有一个方法，那么可以将该类转换为一个函数
# 该函数返回一个闭包

class TT(object):
    def __init__(self, a):
        self.a = a

    def add(self, b):
        return self.a + b

a1 = TT(1)
a2 = TT(2)
print a1.add(3)
print a2.add(3)

def newadd(a):
    def add(b):
        return a + b
    return add

add1 = newadd(1)
add2 = newadd(2)
assert add1(2) == 3
assert add2(2) == 4
