#!/usr/bin/env python3
# encoding: utf-8

# python2 无论采用文本形式还是二进制形式，读取的都是str
# python3 采用文本形式读取的是str，采用二进制形式读取的是bytes
# python3 中将unicode和str两种类型合二为一了
with open("testfile.txt", "rb") as f:
    data = f.read()
    print(type(data))
    print(data.decode("utf-8"))


with open("testfile.txt", "wb") as f:
    text = "0 1 2 3456789"
    f.write(text.encode("utf-8"))

import array
nums = array.array('i', [1, 2, 3, 4])
with open('data.bin','wb') as f:
    f.write(nums)

with open("data.bin", "rb") as f:
    a = array.array('i', [0,0,0,0])
    f.readinto(a)
    print(list(a))
