#! /usr/bin/python

def double(val):
    return val * 2

a = [1,2,3,4,5,6]

for x in map(double, a):
    print(x, end=" ")
print()
