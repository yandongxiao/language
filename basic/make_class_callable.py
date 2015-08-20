#! /usr/bin/python

class Test :
    def __init__(self):
        print("__init__")

    def __call__(elsf, param):
        print("__call__")

key = Test();

key("nihao")
