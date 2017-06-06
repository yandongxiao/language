#!/usr/bin/env python
# encoding: utf-8

class Countdown(object):
    def __init__(self, val):
        self._val = val

    def __iter__(self):
        i = self._val
        while i >= 0:
            yield i
            i -= 1

    # 注意是__reversed__, not __reverse__
    def __reversed__(self):
        i = 0
        while i <= self._val:
            yield i
            i += 1

C = Countdown(5)
for k in C:
    print k,
print

for k in reversed(C):
    print k,
