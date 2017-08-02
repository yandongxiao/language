#! /usr/bin/env python
# encoding: utf-8

import time
import threading

# Code to execute in an independent thread
def countdown(n, started_evt):
    print("countdown starting")
    started_evt.set()
    while n > 0:
        print("T-minus", n)
        n -= 1
        time.sleep(5)

# Create the event object that will be used to signal startup
started_evt = threading.Event()

# Launch the thread and pass the startup event
print("Launching countdown")
t = threading.Thread(target=countdown, args=(10, started_evt))
t.start()

# Wait for the thread to start
started_evt.wait()
print("countdown is running")
