#!/usr/bin/env python3
# encoding: utf-8

# 输出到文件
with open("testfile.txt", "wt") as f:
    print("hello-world", file=f)

# sep and end
print(1,2,"nihao")
print(1,2,"nihao", sep=",")
print(1,2,"nihao", end="!!\n")

