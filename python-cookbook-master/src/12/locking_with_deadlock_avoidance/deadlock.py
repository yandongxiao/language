#! /usr/bin/env python
# encoding: utf-8

import threading
from contextlib import contextmanager

# Thread-local state to stored information on locks already acquired
# 当前线程的堆栈
_local = threading.local()

# contextmanager 很轻松的实现一个上线文管理协议
@contextmanager
def acquire(*locks):
    # Sort locks by object identifier
    locks = sorted(locks, key=lambda x: id(x))

    # 中间这一段是防御性编程
    # Make sure lock order of previously acquired locks is not violated
    acquired = getattr(_local, 'acquired', [])
    if acquired and max(id(lock) for lock in acquired) >= id(locks[0]):
        raise RuntimeError('Lock Order Violation')

    # Acquire all of the locks
    acquired.extend(locks)
    _local.acquired = acquired
    try:
        for lock in locks:
            lock.acquire()
        yield
    finally:
        # Release locks in reverse order of acquisition
        for lock in reversed(locks):
            lock.release()
        del acquired[-len(locks):]
