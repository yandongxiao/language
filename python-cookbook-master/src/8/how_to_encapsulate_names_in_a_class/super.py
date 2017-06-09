#!/usr/bin/env python3
# encoding: utf-8

class A:
    def spam(self):
        print('A.spam')

class B(A):
    def spam(self):
        print('B.spam')
        # python3的调用父类的方法
        super().spam()

b = B()
b.spam()
