#!/usr/bin/env python
# encoding: utf-8

import threading
import time

# the instance’s values will be different for separate threads.
def run(v, l):
    l.a = v
    time.sleep(1)
    print l.a

if __name__ == "__main__":
    l = threading.local()
    threading.Thread(target=run, args=(1, l)).start()
    threading.Thread(target=run, args=(2, l)).start()
