#!/usr/bin/env python3
# encoding: utf-8

class sample(object):
    def __init__(self):
        self.counter = 0
    def new(self):
        self.c2 = 10

s = sample()

# 可以在任意的类方法中定义属性
s.new()
print(s.c2)

# 我们可以在类定义外定义属性
setattr(s, "name", "jack")
print(s.name)
