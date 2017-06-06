#!/usr/bin/env python
# encoding: utf-8

from collections import deque

class History(object):
    def __init__(self, lines, maxlen):
        self.queue = deque(maxlen=maxlen)
        self.lines = lines

    def __iter__(self):
        for n, line in enumerate(self.lines, 1):
            self.queue.append((n,line))
            yield line


with open("somefile.txt") as f:
    lines = History(f, 3)
    for line in lines:
        if "python" in line:
            for n, l in lines.queue:
                print('{}:{}'.format(n, l)),
