#! /usr/bin/env python3

class A(object):
    def __init__(self):
        self.num2 = 100

class Test(A):
    def __init__(self):
        self.num  = 10
        super().__init__()

    def __getitem__(self, key):
        print("__getitem__ called")
        if key == 'num':
            return 10     #called

    def __getattr__(self, key):
        print("__getattr__ called")
        return "nihao"

    def __setattr__(self, key, val):
        print("__setattr__ called")
        object.__setattr__(self, key, val)

    def __getattribute__(self, key):
        print("__getattribute__ called")
        return object.__getattribute__(self, key)    # wiil create an error

tt = Test()
#assert getattr(tt, 'num') == 10     # __getattribute__ called
num = tt.num = 20
print(tt.num)
print(tt["num"])
print(tt.num2)


