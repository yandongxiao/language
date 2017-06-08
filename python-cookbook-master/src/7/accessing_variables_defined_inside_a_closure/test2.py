#!/usr/bin/env python
# encoding: utf-8

import sys

class Instance(object):
    def __init__(self):
        locals = sys._getframe(1).f_locals  # 返回的是一个dict
        # 对__dict__只是更新，不能全盘覆盖
        self.__dict__.update((name, val) for name, val in locals.items()
                                    if callable(val))

    # NOTE：为什么没有复用__dict__["__len__"]呢？
    def __len__(self):
      return self.__dict__["__len__"]()

def Stack():
    stack = []

    def push(v):
        stack.append(v)

    def pop():
        return stack.pop()

    def __len__():
        return len(stack)

    # 不再返回一个闭包函数，而是返回一个特殊的类实例
    return Instance()

if __name__ == '__main__':
    s = Stack()
    print(s)
    s.push(10)
    s.push(20)
    s.push('Hello')
    print(len(s))
    print(s.pop())
    print(s.pop())
    print(s.pop())
