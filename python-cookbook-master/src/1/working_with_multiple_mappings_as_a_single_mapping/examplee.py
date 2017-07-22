#!/usr/bin/env python3
# encoding: utf-8

a = {'x': 1, 'z': 3 }
b = {'y': 2, 'z': 4 }

from collections import ChainMap

nmap = ChainMap(a, b)
print(nmap['x'])
print(nmap['z'])
print(nmap['y'])
