#!/usr/bin/env python
# encoding: utf-8

import time
import threading

def runner(cnt=3):
    for i in range(0, cnt):
        print("helloworld")
        time.sleep(1)

# 1. 后台线程无法等待, join方法失效了
thread = threading.Thread(target=runner, args=(10,))
thread.setDaemon(True)
thread.start()
time.sleep(1)
