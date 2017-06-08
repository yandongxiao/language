#! /usr/bin/env python3
# This example is about the problem of carrying extra state around
# through callback functions.   To test the examples, this very
# simple code emulates the typical control of a callback.

# 回调函数使用外部变量的四种方法：
# 1. 类
# 2. closure
# 3. coroutine
# 4. from functools import partial

def apply_async(func, args, *, callback):
    # Compute the result
    result = func(*args)

    # Invoke the callback with the result
    callback(result)

# A simple function for testing
def add(x, y):
    return x + y

# (a) A simple callback example

print('# --- Simple Example')

def print_result(result):
    print("Got:", result)

apply_async(add, (2, 3), callback=print_result)
apply_async(add, ('hello', 'world'), callback=print_result)

# (b) Using a bound method
# 让回调函数访问更多的外部变量的方式是：传递一个方法
print('# --- Using a bound-method')

class ResultHandler:
    def __init__(self):
        # 外部变量被封装在类实例的成员当中
        self.sequence = 0
    def handler(self, result):
        self.sequence += 1
        print('[{}] Got: {}'.format(self.sequence, result))

r = ResultHandler()
apply_async(add, (2, 3), callback=r.handler)
apply_async(add, ('hello', 'world'), callback=r.handler)

# (c) Using a closure
# 如果一个类只有一个方法，那么可以通过闭包函数解决
print('# --- Using a closure')

def make_handler():
    sequence = 0
    def handler(result):
        nonlocal sequence   # 否则就是use before assignment
        sequence += 1
        print('[{}] Got: {}'.format(sequence, result))
    return handler

handler = make_handler()
apply_async(add, (2, 3), callback=handler)
apply_async(add, ('hello', 'world'), callback=handler)


# (d) Using a coroutine(协程)

print('# --- Using a coroutine')
# 它显得更加简洁，因为总共就一个函数而已
def make_handler():
    sequence = 0
    while True:
        result = yield  # 可以不使用括号
        sequence += 1
        print('[{}] Got: {}'.format(sequence, result))

handler = make_handler()
next(handler)    # 启动协程
apply_async(add, (2, 3), callback=handler.send)
apply_async(add, ('hello', 'world'), callback=handler.send) # 使用send作为回调函数
# NOTE: 没有关闭协程

# (e) Partial function application
# 没毛病
print('# --- Using partial')

class SequenceNo:
    def __init__(self):
        self.sequence = 0

def handler(result, seq):       #it is not a function of SequenceNo
    seq.sequence += 1
    print('[{}] Got: {}'.format(seq.sequence, result))

seq = SequenceNo()
from functools import partial   #So,partial is used to pass a argument to other fucntion.

apply_async(add, (2, 3), callback=partial(handler, seq=seq))
#apply_async(add, (2, 3), seq.handler)
apply_async(add, ('hello', 'world'), callback=partial(handler, seq=seq))
