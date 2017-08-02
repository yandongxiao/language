#! /usr/bin/env python
# encoding: utf-8

# 为什么使用Condition，而非是信号量来实现
# 1. 信号量用于两个线程之间是可以的，一个生产，一个消费。
# 如果有多个生产者或消费者，信号量的值可能会在[-n, n]之间，即
# 不能保证同时只有一个生产者或消费者工作，进一步将，heaq的操作会有多线程同时操作的可能

# 是否可以用锁来替代Condition
# 锁是一种资源，为了保证线程安全，无论是消费者还是生产者，都需要先获取锁，然后再操作队列
# 而如果消费者获取锁以后，发现队列为空，还需要主动释放锁。。

import heapq
import threading
import time

# 原则1：两个线程共享一个对象，queue也是这样做的
class PriorityQueue:        # 实现了一个线程安全的优先级队列
    def __init__(self):
        self._queue = []
        self._count = 0
        self._cv = threading.Condition()

    def put(self, item, priority):
        with self._cv:  # 获取锁
            # 向heaq中添加元素
            heapq.heappush(self._queue, (-priority, self._count, item))
            self._count += 1    # 保证队列元素的唯一性
            self._cv.notify()

    def get(self):
        with self._cv:  # 获取锁
            while len(self._queue) == 0:
                self._cv.wait()
            return heapq.heappop(self._queue)[-1]


def producer(q):
    print('Producing items')
    q.put('C', 5)
    q.put('A', 15)
    q.put('B', 10)
    q.put('D', 0)
    q.put(None, -100)   # 结尾元素
    print('Producer done')


def consumer(q):
    time.sleep(5)
    print('Getting items')
    while True:
        item = q.get()
        if item is None:
            break
        print('Got:', item)
    print('Consumer done')


if __name__ == '__main__':
    q = PriorityQueue()
    t1 = threading.Thread(target=producer, args=(q,))
    t2 = threading.Thread(target=consumer, args=(q,))
    t1.start()
    t2.start()
    t1.join()
    t2.join()
