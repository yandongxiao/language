#!/usr/bin/env python
# encoding: utf-8

from a.b import *
from a.c import *
from a import c

print "main"
print dir()
print c.cn
print c._cx     # 私有变量也是可以访问到的
print c.__cyy
print c.__czz__
