#!/usr/bin/env python
# encoding: utf-8

from collections import deque

# 这里的困境就在于将模式匹配抽离出来以后，
# 如何暴露buffer的问题
# 导致yield暴露的内容太多
def histlines(lines, history=2):
    buffer = deque(maxlen=history)
    # 注意enumerate带来的好处
    for n, line in enumerate(lines, 1):
        yield n, line, buffer
        buffer.append((n, line))


with open("somefile.txt") as f:
    lines = histlines(f)
    for n, line, buffer in lines:
        if "python" in line:
            print line,
            for _, l in buffer:
                print "    " + l,
