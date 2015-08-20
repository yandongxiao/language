#! /usr/bin/python

class Person :
    def __init__(self):
        self.a = 10

p = Person()
val = getattr(p, "a")

print(val)
