#!/usr/bin/env python
# encoding: utf-8

# NOTE: 调用者先开始接收

def test():
    num1 = yield 1
    assert "hello" == num1
    num2 = yield 2
    print("===" + str(num2))


# 方法1
# send发送给当前yield，下一个yield返回的内容被send接收。
# NOTE：不是同一个yield哟
t = test()
v = t.send(None)    # 接收1
assert v==1
v = t.send("hello") # 发送"hello", 并接收2
assert v==2

# 方法2
t = test()
v = t.next()
assert v == 1
v = t.send("hello")
assert v==2

try:
    t.send("world")     # 最后一次仅仅是发送操作就行
except StopIteration as e:
    print(e)
