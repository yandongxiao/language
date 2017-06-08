#!/usr/bin/env python
# encoding: utf-8

def get(b = []):
    b.append(1)
    print b

get()
get()
get()

_obj = object()
def set(b = _obj):
    if b is _obj:
        print "no arg"
    else:
        print b

set()
set(None)
set(1)
