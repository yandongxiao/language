#! /usr/bin/python

x = 10
try:
    x = x / 0
except Exception as x:
    print("error:", x)
print (x) # x is not define.
