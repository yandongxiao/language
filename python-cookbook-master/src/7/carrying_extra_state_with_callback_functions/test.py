#!/usr/bin/env python3
# encoding: utf-8

# 注意星号的使用
def call_func(func, args, *, callback):
    result = func(*args)    # 注意星号
    callback(result)

def add(a, b):
    return a + b

# method0 - 回调函数的输入全部来自函数的形参
def add_cb(result):
    print("add_cb: %s" % str(result))
call_func(add, (1, 2), callback=add_cb) # 传递一个序列
call_func(add, ("hello", "world"), callback=add_cb) # 传递一个序列

# method2 - 回调函数的输入来自一个对象实例
class sample1(object):
    def __init__(self):
        self.counter = 0
    def handler(self, result):
        self.counter += 1
        print("class handler: %d:%s" % (self.counter, str(result)))

s = sample1()
call_func(add, (1, 2), callback = s.handler)
call_func(add, ("hello", "world"), callback = s.handler)    # NOTE: 对象方法也可以作为回调函数

# method3 - 如果一个类只有方法，通常可以用closure函数替代
def sample2():
    counter = 0
    def handler(result):
        nonlocal counter    # 必要的
        counter += 1
        print("closure handler: %d:%s" % (counter, str(result)))
    return handler

s=sample2()
call_func(add, (1, 2), callback = s)
call_func(add, ("hello", "world"), callback=s)

# method3 - coroutine 代替 closure， 让程序变得更加自然
def sample3():
    counter = 0
    while True:
        result = yield
        counter += 1
        print("coroutine handler: %d:%s" % (counter, str(result)))

s = sample3()
next(s)
call_func(add, (1, 2), callback = s.send)
call_func(add, ("hello", "world"), callback=s.send)     # 传递的是s.send


# method4 - 利用partitial对函数接口进行二次封装
from functools import partial
def add_cb(counter, result):
    print("partial handler: %d:%s" % (counter, str(result)))
s = partial(add_cb, 1)      # NOTE: 回调函数之间并没有维持状态
call_func(add, (1, 2), callback = s)
call_func(add, ("hello", "world"), callback=s)     # 传递的是s.send

# 改进方法
class sample4(object):
    def __init__(self):
        self.counter = 0

def add_cb2(result, obj):
    obj.counter += 1
    print("partial handler: %d:%s" % (obj.counter, str(result)))

s = partial(add_cb2, obj=sample4())      # NOTE: 回调函数之间并没有维持状态
call_func(add, (1, 2), callback = s)
call_func(add, ("hello", "world"), callback=s)     # 传递的是s.send
