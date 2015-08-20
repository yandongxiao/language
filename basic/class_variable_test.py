#! /usr/bin/python

a = 0   # global var
class Test():
    global a    # you can also declare a global b, event it is not assigned out side.
    a = 10      # a is not an attribute of Test
    b = 20      # B is.

    def __init__(self):
        global a
        a = 50

t = Test()
print(a)
#print(Test.a)   # 'Test' object has no attribute 'a'
print(Test.b)


class Test:
    def __init__(self):
        pass
t=Test()
t.a=10  #add attr here


