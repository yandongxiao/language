#! /usr/bin/env python3
#encoding: utf-8

# Callback functions can be inlined into a function using generators and coroutines.
# 普通模式下，一定有大量的apply_async调用，伴随着大量的回调函数，python文件的可读性被破坏。
# 利用生产者和消费者模式，构建generators and coroutines，使得回调函数的处理可以集中到一块。甚至
# 回调函数无需是函数。

# Inlined callback implementation
from queue import Queue
from functools import wraps

# Sample function to illustrate callback control flow
def apply_async(func, args, *, callback):
    # Compute the result
    result = func(*args)
    # Invoke the callback with the result
    callback(result)

class Async:
    def __init__(self, func, args):
        self.func = func
        self.args = args

# 这是一个装饰器
def inlined_async(func):
    @wraps(func)
    def wrapper(*args):
        # 执行test函数, 返回生成器对象. 注意是装饰器拿到了生成器对象
        # 装饰器作为了消费者
        f = func(*args)
        result_queue = Queue()
        result_queue.put(None)
        while True:
            # 如果没有数据到来，协程就会在此处被block住
            result = result_queue.get()
            try:
                # NOTE:
                # 给test返回结果, 并等待接收Async实例
                # 第一次发送给协程的数据是None, 目的只是为了接收数据
                a = f.send(result)
                # 计算结果
                apply_async(a.func, a.args, callback=result_queue.put)
            except StopIteration:   # 需要主动捕获StopIteration异常
                break
    return wrapper

# Sample use
def add(x, y):
    return x + y

# 等价于
# test = inlined_async(test)
@inlined_async
def test():         # 被封装的test函数变成了生产者
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

    # 采用多进程的方式，进程池的大小和当前系统有关系
    # 当前进程运行生产者和消费者函数，即test和inlined_async
    # inlined_async将自己的任务派发给子进程去处理
    # from queue import Queue 看来这个Queue是进程安全的
    print('# --- Multiprocessing test')
    import multiprocessing
    pool = multiprocessing.Pool()
    apply_async = pool.apply_async
    test()
