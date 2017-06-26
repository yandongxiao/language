#!/usr/bin/env python
# encoding: utf-8


from abc import ABCMeta, abstractmethod

class A(object):
    __metaclass__ = ABCMeta
    @abstractmethod
    def spam(self):
        print("A: spam")

class B(A):
    def spam(self):
        A.spam(self)
        print("B: spam")

b = B()
b.spam()

class C(A):
    spam = 20

c = C()
print(c.spam)

class D:
    pass

A.register(D)
d = D()
print isinstance(d, A)
print issubclass(D, A)
