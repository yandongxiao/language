#! /usr/bin/python


def dg(num):
    a = 10
    if(num<10):
        print("a == ", a)   # a is alwayse 10.
        a += 1
        num += 1
        dg(num)
    else:
        return

dg(8)

print(a)
a = 10  #error



def aaa():
    import sys
    help(sys)

aaa()
help(sys)   #error
