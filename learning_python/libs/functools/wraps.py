#!/usr/bin/env python
# encoding: utf-8

import sys
sys.path = sys.path[1:]

from functools import wraps

def wrapper(f):
    @wraps(f)
    def newf():
        print "begin"
        f()
        print "end"
    return newf

@wrapper
def printer():
    print "helloworld"

printer()
print printer.__name__
