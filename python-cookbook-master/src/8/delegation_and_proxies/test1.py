#!/usr/bin/env python
# encoding: utf-8

class A:
    def foo(self):
        print("A.foo")

class B:
    def __init__(self):
        self._a = A()

    def bar(self):
        print("B.bar")

    def __getattr__(self, name):
        return getattr(self._a, name)

b = B()
b.foo()
b.bar()
