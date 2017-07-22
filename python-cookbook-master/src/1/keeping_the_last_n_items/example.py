#!/usr/bin/env python
# encoding: utf-8

from collections import deque

# method - 1
def search1(lines, keyword, maxlen = 3):
    queue = deque(maxlen=maxlen)
    for line in lines:
        if keyword in line:
            yield line, queue
        queue.append(line)

# method - 2
import fnmatch
def search2(lines, keyword, maxlen = 3):
    queue = deque(maxlen=maxlen)
    for line in lines:
        if fnmatch.fnmatch(line, keyword):
            yield line, queue
        else:
            queue.append(line)

# with as 的工作原理：see http://blog.kissdata.com/2014/05/23/python-with.html
# 1. 捕获异常；2. 关闭句柄
with open("somefile.txt") as lines:
    for line, prevlines in search2(lines, "* to *"):
        print line, prevlines

