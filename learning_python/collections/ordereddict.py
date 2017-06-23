#!/usr/bin/env python
# encoding: utf-8

from collections import OrderedDict

d = OrderedDict()
d["first"] = 1
d["second"] = 2
d["three"] = 3

for key in d:
    print d[key]

