#! /usr/bin/python

from operator import itemgetter

f = itemgetter(1)
a = [1, 2, 3]
b = ["hello", "world"]
print f(a)
print f(b)

c = {"name":"jack", "age":10}
d = {"name":"bob", "age":10}
f = itemgetter("name")
print f(c)
print f(d)
