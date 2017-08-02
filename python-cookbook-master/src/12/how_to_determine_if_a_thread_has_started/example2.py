#! /usr/bin/env python
# encoding: utf-8

import threading
import time

class PeriodicTimer:
    def __init__(self, interval):
        self._interval = interval
        self._flag = 0
        # 与Event对象的创建方法是一样的
        self._cv = threading.Condition()

    def start(self):
        t = threading.Thread(target=self.run)
        t.daemon = True
        t.start()

    def run(self):
        '''
        Run the timer and notify waiting threads after each interval
        '''
        while True:
            # since notify() does not release the lock, its caller should.
            # Condition 支持上下文管理协议，目的是为了隐藏释放底层锁的问题，每次while循环都会释放该锁
            # 为什么Event就是一次性的，而Condition就可以重复利用呢？ 就是因为Condition的底层还有一个锁
            # 为什么notify_all方法会导致两个线程并行返回呢？不是说，Once awakened or timed out, it re-acquires the lock and returns.
            # 按照上面的道理，虽然是notify_all，但是最终也只能有一个线程能获取该锁。
            # 没错，只有一个线程会获取该锁，但是另外一个线程从睡眠状态醒过来，只等着前面那个线程释放锁，就可以工作了。它不需要再次被唤醒
            time.sleep(self._interval)
            with self._cv:
                 self._flag ^= 1
                 self._cv.notify_all()

    def wait_for_tick(self):
        '''
        Wait for the next tick of the timer
        '''
        with self._cv:      # 释放锁的速度很快的
            # 注意：为什么使用while循环？
            # last_flag == self._flag 就是所谓的Condition了，如果条件不满足，逻辑上当然不应该醒来
            last_flag = self._flag
            while last_flag == self._flag:
                self._cv.wait()     # 会主动将锁释放, 并进入睡眠状态


# Example use of the timer
ptimer = PeriodicTimer(1)
ptimer.start()

# Two threads that synchronize on the timer
def countdown(nticks):
    while nticks > 0:
        ptimer.wait_for_tick()
        print("T-minus", nticks)
        nticks -= 1

def countup(last):
    n = 0
    while n < last:
        ptimer.wait_for_tick()
        print("Counting", n)
        n += 1

threading.Thread(target=countdown, args=(5,)).start()
threading.Thread(target=countup, args=(5,)).start()
