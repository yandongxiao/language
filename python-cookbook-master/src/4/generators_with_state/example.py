#! /usr/bin/env python3
# encoding: utf-8

# Example of a generator with extra state that can be
# accessed.   Simply define as a class!

from collections import deque

# 如果使用生成器函数，生成器的中间状态都需要通过yield函数来返回
# 通过类的方式，可以更优雅的处理上面的问题
class linehistory:
    def __init__(self, lines, histlen=3):
        self.lines = lines
        self.history = deque(maxlen=histlen)

    # __iter__ 返回的是可迭代对象
    # 1. iter(内部容器)，做一个内部容器的代理；
    # 通过yield，将__ier__函数变成一个生成器
    def __iter__(self):
        # 文件带上行号的方法
        for lineno, line in enumerate(self.lines, 1):
            self.history.append((lineno, line))
            yield line

with open('somefile.txt') as f:
     lines = linehistory(f)
     for line in lines:
         if 'python' in line:
             for lineno, hline in lines.history:
                 print('{}:{}'.format(lineno, hline), end='')
