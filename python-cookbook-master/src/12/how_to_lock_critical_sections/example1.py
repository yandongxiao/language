#! /usr/bin/env python
# encoding: utf-8

# 使用一个锁对一个可变变量进行保护，同时将他们封装成一个类，那么类对象就是线程安全的
# RLock是可重入的锁，即一个线程可以再次获取同一个锁
# 信号量比锁更耗费资源，所以能使用锁的地方，不使用信号量
# 信号量主要是用来控制并发数的

import threading

class SharedCounter:
    '''
    A counter object that can be shared by multiple threads.
    '''

    def __init__(self, initial_value = 0):
        self._value = initial_value
        self._value_lock = threading.Lock()

    def incr(self,delta=1):
        '''
	    Increment the counter with locking
	    '''
        with self._value_lock:
             self._value += delta

    def decr(self,delta=1):
        '''
        Decrement the counter with locking
        '''
        with self._value_lock:
             self._value -= delta

def test(c):
    for n in range(1000000):
        c.incr()
    for n in range(1000000):
        c.decr()

if __name__ == '__main__':
    c = SharedCounter()
    t1 = threading.Thread(target=test, args=(c,))
    t2 = threading.Thread(target=test, args=(c,))
    t3 = threading.Thread(target=test, args=(c,))
    t1.start()
    t2.start()
    t3.start()
    print('Running test')
    t1.join()
    t2.join()
    t3.join()

    assert c._value == 0
    print('Looks good!')
