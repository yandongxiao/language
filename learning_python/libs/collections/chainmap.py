#!/usr/bin/env python3
# encoding: utf-8

from collections import ChainMap

a = {"name":"jack"}
b = {"age":10}

c = ChainMap(a, b)
for k in c:
    print(k)
