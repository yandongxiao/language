#!/usr/bin/env python
# encoding: utf-8

import time
import threading

def runner(cnt=3):
    for i in range(0, cnt):
        print("helloworld")
        time.sleep(1)

# 1. 创建了一个真正的系统级的线程
# 2. 子线程与主线程之间不再有任何关联，即使主线程关掉之后，子线程仍然可以运行
# 3. 主线程不能控制子线程的生死，也不能向子线程发送信号
# 4. 主线程唯一可做的事情是：要么将子线程设置为daemon模式，主线程退出时，子线程被杀死；
#    要么，执行t.join方法，等待子线程执行结束
# 5. 线程之间可以共享变量，可以通过变量值的更改，来完成对线程的控制。但是这样做的前提是，
#    所有的IO操作都不能无限制的阻塞下去，需要使用定时IO
# 6. NOTE: 由于全局解释锁（GIL）的原因，Python 的线程被限制到同一时刻只允许一个线程
#    执行这样一个执行模型。所以，Python 的线程更适用于处理I/O和其他需要并发执行的阻塞
#    操作（比如等待I/O、等待从数据库获取数据等等），而不是需要多处理器并行的计算密集型任务。
# 7. 不要试图去继承Thread类，这样只会限制你的代码的可能性
thread = threading.Thread(target=runner, args=(10,))
thread.start()
