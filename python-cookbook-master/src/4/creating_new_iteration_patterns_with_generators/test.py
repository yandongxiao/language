#!/usr/bin/env python
# encoding: utf-8

def frange(start, end, step):
    val = start
    while val < end:
        yield val
        val += step

for f in frange(0, 2, 0.5):
    print f

