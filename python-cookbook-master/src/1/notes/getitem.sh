#! /usr/bin/python

class Test:
    def __init__(self):
        self.lt = [1,2,3,4]

    def __getitem__(self, key):
        return self.lt[key]

tt = Test()
assert tt[0] == 1
