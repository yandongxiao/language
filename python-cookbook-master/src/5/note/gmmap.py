#!/usr/bin/env python
# encoding: utf-8

import mmap
import os

filename = "testfile.txt"

# 1. 请使用os.open函数
# 2. mmap.ACCESS_WRITE 和 mmap.ACCESS_READ 不能同时使用
# 3. 内存映射一个文件并不会导致整个文件被读取到内存中
# 4. 多个Python解释器内存映射同一个文件，得到的 mmap 对象能够被用来在解释器直接交换数据。
# 也就是说，所有解释器都能同时读写数据，并且其中一个解释器所做的修改会自动呈现在其他解释器中。 很明显，这里需要考虑同步的问题。
fileno = os.open(filename, os.O_RDWR)
size = os.path.getsize(filename)
m = mmap.mmap(fileno, size, access=mmap.ACCESS_WRITE)

print(len(m))
m[0:10] = "helloworld"
m.close()


with open(filename, 'rb') as f:
    print(f.read(10))

