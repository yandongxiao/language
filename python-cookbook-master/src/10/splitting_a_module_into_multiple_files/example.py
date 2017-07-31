# /usr/bin/env python
# encoding: utf-8

print "====method1===="
import mymodule
a = mymodule.A()
a.spam()
b = mymodule.B()
b.bar()

print "====method2===="
from mymodule.a import A
from mymodule.b import B
a = A()
a.spam()
b = B()
b.bar()
A = 10
A = 20

print "====method3===="
from mymodule import A, B
a = A()
a.spam()
b = B()
b.bar()
