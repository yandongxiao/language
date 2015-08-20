#! /usr/bin/python
"""
def func():
    def a1():
        nonlocal a  # no binding for nonlocal 'a' found
        print(a)
"""

def func():
    def a1():
        nonlocal a
        print(a)
    a=10    #make sure a is defined befor the call statement.
    a1()
func()


def func():
    def a1():
        nonlocal a
        a += 1
        print(a)
    a=10    #make sure a is defined befor the call statement.
    return a1
a=func()
a()
a()
b=func()
b()
