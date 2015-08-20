#! /usr/bin/python

def f1():
    x = 88
    x += 1
    def f2(x=x):
        print(x)
    return f2

a=f1()
a() #not 88

