#!/usr/bin/env python
# encoding: utf-8

class myclass(object):
    # 1. __slots__ 是一个类属性
    # 2. __slots__ 并不能阻止用户创建任何类方法
    # 3. 实例变量只能创建age域
    __slots__ = ('age')

    def __len__(self):
        return 10

    def name(self):
        return "name"


print(myclass())
print(len(myclass()))
print(myclass().name())

a = myclass()
a.age = 10
print(a.age)
