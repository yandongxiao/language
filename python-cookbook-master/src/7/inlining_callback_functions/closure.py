#!/usr/bin/env python
# encoding: utf-8

# NOTE: 调用者先开始接收

def test():
    num1 = yield 1
    print(num1)
    num2 = yield 2
    print("===" + str(num2))


# 方法1
t = test()
v = t.send(None)    # 接收1
print(v)
v = t.send("hello") # 发送"hello", 并接收2
print(v)

# 方法2
t = test()
v = t.next()
print(v)
v = t.send("hello")
print v

try:
    t.send("world")     # 最后一次仅仅是发送操作就行
except StopIteration as e:
    print(e)
