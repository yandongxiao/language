#!/usr/bin/env python3
# encoding: utf-8

# x属性也属于python3
try:
    with open("testfile.txt", "xt") as f:
        f.write("helloworld")
except FileExistsError as e:    #语法类似于with..as
    print(e)
