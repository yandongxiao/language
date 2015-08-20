#! /usr/bin/python

class Test:
    def __init__(self):
        self.num  = 10

    def __getitem__(self, key):
        print("__getitem__ called")
        if key == 'num':
            return 10     #called

    def __getattribute__(self, key):
        print("__getattribute__ called")
        return self.num     # wiil create an error

tt = Test()
#assert getattr(tt, 'num') == 10     # __getattribute__ called
num = tt.num = 20
