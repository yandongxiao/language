#!/usr/bin/env python
# encoding: utf-8

def d3(func):
    print "d3"
    return func

def d2(func):
    print "d2"
    return func

def d1(func):
    print "d1"
    return func

# d3(d2(d1(hello)))
@d3
@d2
@d1
def hello():
    print "hello"

hello()
hello()
