#!/usr/bin/env python
# encoding: utf-8

class Y(object):
    def __init__(self):
        self.a = 10

    def __getattr__(self, name):
        return name

y = Y()
print y.a
print y.b
print getattr(y, "a")
print getattr(y, "b")
