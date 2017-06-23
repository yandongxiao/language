#!/usr/bin/env python
# encoding: utf-8

from collections import defaultdict

d = defaultdict(list)
d["animal"].append("tom")
d["animal"].append("jerry")
print dict(d)
