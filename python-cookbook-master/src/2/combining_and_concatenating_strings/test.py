#!/usr/bin/env python
# encoding: utf-8

# 连接
# 1. 使用+连接字符串
# +连接在对小字符串进行连接和格式化的时候，非常简单；
# 但是大量字符串的+连接会导致大量临时字符串对象的产生和垃圾回收
a = "hello"
b = "world"
print a + b
print a + " " + b

def sample():
    yield "Is"
    yield "Chicago"
    yield "Not"
    yield "Chicago?"

# 2. 使用join方法
# 不推荐的字符串连接方法
#statements = ""
#for i in sample():
#    statements += i
#    statements += " "
#print statements

print " ".join(sample())

# 3. 输出到终端
# write方法是一次系统调用，
# 如果输出的是大量小的字符串，应该先join到一起，write到文件中
import sys
sys.stdout.write("hello")
sys.stdout.write("world")
sys.stdout.write("\n")

# 4. 对第三种方法的优化
def combine(source, maxsize):
    buffer = []
    size = 0
    for data in source:
        buffer.append(data)
        size += len(data)
        if size > maxsize:
            yield ''.join(buffer)
            buffer = []
            size = 0
    yield ''.join(buffer)

print list(combine(sample(), 10))
