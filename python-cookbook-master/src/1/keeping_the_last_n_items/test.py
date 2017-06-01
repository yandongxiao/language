#!/usr/bin/env python
# encoding: utf-8

from collections import deque

def search(lines, substr, prev_count):
    buf = deque(maxlen=prev_count)
    for line in lines:
        if substr in line:
            yield line, buf
        buf.append(line)


with open("./somefile.txt") as f:
    for line, prev_lines in search(f, "python", 5):
        for l in prev_lines:
            print l,
        print line,
        print "-"*20
