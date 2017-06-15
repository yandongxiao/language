#! /usr/bin/env python3
#encoding: utf-8

# Callback functions can be inlined into a function using generators and coroutines.
# 利用Async 和 inlined_async 构建了通过yield来传递callback的环境

# Sample function to illustrate callback control flow
def apply_async(func, args, *, callback):
    # Compute the result
    result = func(*args)
    # Invoke the callback with the result
    callback(result)

# Inlined callback implementation
from queue import Queue
from functools import wraps

class Async:
    def __init__(self, func, args):
        self.func = func
        self.args = args

# 这是一个装饰器
def inlined_async(func):
    @wraps(func)
    def wrapper(*args):
        f = func(*args)             # 执行test函数, 返回test协程
        result_queue = Queue()
        result_queue.put(None)
        while True:
            # 如果没有数据到来，协程就会在此处被block住
            result = result_queue.get()
            try:
                # NOTE:
                # 给协程test发送数据, 并等待接收Async实例
                # 第一次发送给协程的数据是None, 目的只是为了接收数据
                a = f.send(result)
                # 根据test返回的指令，执行。
                # 并将结果放到Queue当中准备返回
                apply_async(a.func, a.args, callback=result_queue.put)
            except StopIteration:   # 需要主动捕获StopIteration异常
                break
    return wrapper

# Sample use
def add(x, y):
    return x + y

# 等价于
# test = inlined_async(test)
@inlined_async      #very strange.
def test():         # test既是一个生成器，也是一个协程
    r = yield Async(add, (2, 3))
    print(r)
    r = yield Async(add, ('hello', 'world'))
    print(r)
    for n in range(10):
        r = yield Async(add, (n, n))
        print(r)
    print('Goodbye')


if __name__ == '__main__':
    # Simple test
    print('# --- Simple test')
    test()

    print('# --- Multiprocessing test')
    import multiprocessing
    pool = multiprocessing.Pool()
    apply_async = pool.apply_async
    test()
