#!/usr/bin/env python
# encoding: utf-8

from collections import deque

def search(lines, pattern, history=5):
    queue = deque(maxlen=history)
    for line in lines:
        if pattern in line:
            yield line, queue
        queue.append(line)

with open("somefile.txt") as f:
    for match, prevlines in search(f, "python"):
        for pline in prevlines:
            print pline,
        print match,
        print '*'*20
