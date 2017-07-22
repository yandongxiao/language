#!/usr/bin/env python
# encoding: utf-8

a = {
   'x' : 1,
   'y' : 2,
   'z' : 3
}

b = {
   'w' : 10,
   'x' : 11,
   'y' : 2
}

print set(a.keys()) & set(b.keys())
print set(a.keys()) - set(b.keys())
print set(a.items()) & set(b.items())
