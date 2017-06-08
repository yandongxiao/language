#!/usr/bin/env python3
# encoding: utf-8

def mkfunc(n):
    def set(v):
        nonlocal n
        n = v

    def get():
        return n

    def call():
        return n
    call.set = set
    call.get = get
    return call

f = mkfunc(10)
assert f() == 10
f.set(20)
assert f() == 20
assert f.get() == 20

class TT(object):
    def __init__(self, v):
        self.v = v

    def set(self, v):
        self.v = v

    def get(self):
        return self.v

    def __call__(self):
        return self.v

f = TT(10)
assert f() == 10
f.set(20)
assert f() == 20
assert f.get() == 20
print("done")
