#! /usr/bin/env python3
# encoding: utf-8

# Example of a generator with extra state that can be
# accessed.   Simply define as a class!

from collections import deque

# 如果你想让你的生成器暴露外部状态给用户， 别忘了你可以简单的将它实现为一个类，
# 然后把生成器函数放到 __iter__() 方法中过去。
class linehistory:
    def __init__(self, lines, histlen=3):
        self.lines = lines
        self.history = deque(maxlen=histlen)

    # __iter__ 返回的是迭代器，常见方法
    # 1. iter(内部容器)，做一个内部容器的代理；
    # 2. 通过yield，将__ier__函数变成一个生成器
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
