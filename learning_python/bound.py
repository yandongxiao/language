#!/usr/bin/env python
# encoding: utf-8

class A:
    def bar( self ):
        print "bar"

a = A()
print(a.bar)    # bound method A.bar

def fooFighters( self ):
    print "fooFighters"

A.fooFighters = fooFighters     # 绑定操作
a2 = A()
print(a2.fooFighters)   # bound method A.fooFighters
print(a.fooFighters)    # bound method A.fooFighters

def barFighters(self):
    print "fooFighters"
a.barFighters = barFighters
print((a.barFighters))  # function barFighters, 非绑定操作，a.barFighters指向了同一个函数

import types
a.barFighters = types.MethodType(barFighters, a)    # barFighters的第一个参数绑定为a
print(a.barFighters)

xxx = types.MethodType(barFighters, a)    # barFighters的第一个参数绑定为a
print(xxx())
