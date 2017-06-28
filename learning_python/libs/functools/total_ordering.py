#!/usr/bin/env python
# encoding: utf-8

import sys
sys.path = sys.path[1:]

from functools import total_ordering

@total_ordering
class Person(object):
    def __init__(self, name):
        self.name = name

    def __eq__(self, p):
        return True if self.name == p.name else False

    def __lt__(self, p):
        return True if self.name < p.name else False

p1 = Person("tom")
p2 = Person("zoo")
assert p2 >= p1
assert p1 < p2
