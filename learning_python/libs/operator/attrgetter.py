#! /usr/bin/env python


class Person(object):
    def __init__(self, name, age):
        self.name = name
        self.age = age

a = Person("alice", 10)
b = Person("bob", 10)

from operator import attrgetter
f = attrgetter("name")
print f(a)
print f(b)
