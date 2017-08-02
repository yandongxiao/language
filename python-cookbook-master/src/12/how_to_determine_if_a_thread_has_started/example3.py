#! /usr/bin/env python3
# encoding: utf-8

import threading
import time

# Worker thread
def worker(n, sema):
    # Wait to be signalled
    sema.acquire()
    # Do some work
    print("Working", n)

# Create some threads
# 小于或者等于0的情况下，acquire操作会被阻塞
sema = threading.Semaphore(1)
nworkers = 10
for n in range(nworkers):
    t = threading.Thread(target=worker, args=(n, sema,))
    t.daemon=True
    t.start()

print('About to release first worker')
time.sleep(5)
sema.release()  # 一次release允许一个线程开始工作
time.sleep(1)
print('About to release second worker')
time.sleep(5)
sema.release()
time.sleep(1)
print('Goodbye')
