#!/usr/bin/env python
# encoding: utf-8

import time
import threading

started_evt = threading.Event()

# Code to execute in an independent thread
def countdown(n):
    print("countdown starting")
    time.sleep(2)
    started_evt.set()

print("Launching countdown")
t = threading.Thread(target=countdown, args=(10, ))
t.start()
started_evt.wait()
print("countdown is running")
