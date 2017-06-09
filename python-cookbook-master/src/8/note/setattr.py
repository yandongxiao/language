#!/usr/bin/env python3
# encoding: utf-8

class Y(object):
    def __init__(self):
        self.a = 10     # __setattr__ will be called

    def __getattr__(self, name):
        return name

    def __setattr__(self, name, value):
        # self.name = value     # 这个操作就不再被允许了
        # 最新的复制方法
        # 1. object.__setattr__(self, name, value)
        print("=======")
        super().__setattr__(name, value)    # 更加推荐的方法

y = Y()
print(y.a)
print(y.b)
print(getattr(y, "a"))
print(getattr(y, "b"))

y.a = 20
print(y.a)
setattr(y, "a", 30)     # __setattr__方法也是会被调用的
