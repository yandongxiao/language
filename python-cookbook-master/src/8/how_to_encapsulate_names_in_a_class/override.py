#!/usr/bin/env python
# encoding: utf-8

# 这里继承于object是比不可少的
class B(object):
    def __init__(self):
        self.v1 = "B"    # 被覆盖
        self.v2 = "B"    # 被继承

    def _m1(self):      # 被覆盖
        print "B:_m1"

    def _m2(self):      # 被继承
        print "B:_m2"

    def __m3(self):      # 防止被覆盖
        print "B:_m3"

class C(B):
    def __init__(self):
        super(C, self).__init__()
        self.v1 = "C"

    def _m1(self):
        #super(C, self)._m1()
        print "C:_m1"

    def __m3(self):
        #super(C, self)._B__m3()
        print "C:_m3"

c = C()
print(c.v1)
print(c.v2)

c._m1()
c._m2()

c._C__m3()
c._B__m3()
