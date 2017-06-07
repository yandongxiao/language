#!/usr/bin/env python
# encoding: utf-8

def sub(l):
    tmp = l[0]
    l[0] -= 1
    return tmp

def add(l):
    tmp = l[0]
    l[0] += 1
    return tmp


class Countdown(object):
    def __init__(self, val):
        self._val = val

    # iter 函数一个鲜为人知的特性是它接受一个可选的 callable 对象
    # 和一个标记(结尾)值作为输入参数。
    # 当以这种方式使用的时候，它会创建一个迭代器， 这个迭代器会不断调用 callable 对象直到返回值和标记值相等为止。
    def __iter__(self):
        # 使得sub函数之间需要传递共享的变量，所以需要利用引用传递
        # 不再通过类成员变量来传递数据
        l = [self._val]
        return iter(lambda: sub(l), 0)

    # 注意是__reversed__, not __reverse__
    def __reversed__(self):
        l = [1]
        return iter(lambda: add(l), self._val+1)

C = Countdown(5)
for k in C:
    print k,
print

for k in reversed(C):
    print k,
