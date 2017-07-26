#! /usr/bin/env python3

# 回调函数使用外部变量的四种方法：
# 1. 不携带任何外部变量
# 2. 传递一个bound方法
# 3. 传递一个闭包
# 4. 传递一个协程
# 5. 利用partial函数，对回调函数接口二次封装

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
        nonlocal sequence
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
apply_async(add, ('hello', 'world'), callback=handler.send)
handler.close()

# (e) Partial function application
print('# --- Using partial')
class SequenceNo:
    def __init__(self):
        self.sequence = 0

def handler(result, seq):
    seq.sequence += 1
    print('[{}] Got: {}'.format(seq.sequence, result))

seq = SequenceNo()
from functools import partial   #So,partial is used to pass a argument to other fucntion.
new_handler = partial(handler, seq=seq)

apply_async(add, (2, 3), callback=new_handler)
apply_async(add, ('hello', 'world'), callback=new_handler)
