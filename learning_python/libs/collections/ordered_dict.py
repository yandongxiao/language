#!/usr/bin/env python
# encoding: utf-8

from collections import OrderedDict

d = OrderedDict()
d["country"] = "china"
d["province"] = "zhejiang"
d["city"] = "hangzhou"

for k in d:
    print k
