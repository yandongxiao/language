#! /usr/bin/env python
# encoding: utf-8

from threading import Thread
import time

class CountdownTask:
    def __init__(self):
        self._running = True

    def terminate(self):
        self._running = False

    def run(self, n):
        while self._running and n > 0:
            print("T-minus", n)
            n -= 1
            time.sleep(5)

c = CountdownTask()
try:
    # 主线程负责将子线程销毁掉，否则CTL+C就不起作用
    t = Thread(target=c.run, args=(10,))
    t.start()
    time.sleep(20)
    print('About to terminate')
finally:
    c.terminate()
    t.join()
    print('Terminated')
