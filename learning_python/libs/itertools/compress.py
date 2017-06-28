#!/usr/bin/env python
# encoding: utf-8

from itertools import compress
for a in compress([1,2,3], [1,0,1]):
    print a
