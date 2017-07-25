#!/usr/bin/env python
# encoding: utf-8

from collections import deque

def search(lines, pattern, history=3):
    buffer = deque(maxlen=history)
    for n, line in enumerate(lines, 1):
        buffer.append((n, line))
        if pattern in line:
            yield buffer
            buffer.clear()


with open("somefile.txt") as f:
    for lines in search(f, "python"):
        for n, l in lines:
            print str(n) + ": " +  l,
        print
