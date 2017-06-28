#!/usr/bin/env python
# encoding: utf-8

import sys
sys.path = sys.path[1:]

from functools import partial

def add(a, b):
    return a + b

def printer(result, verbose):
    if verbose:
        print result

newprinter = partial(printer, verbose=True)
newprinter(add(1, 2))

