#! /usr/bin/env python
# encoding: utf-8

import time
from contextlib import contextmanager

@contextmanager
def timethis(label):
    start = time.time()
    try:
        # yield 之前是__enter__方法，yield之后是__exit__方法，异常在yield处抛出
        yield
    finally:
        end = time.time()
        print('{}: {}'.format(label, end - start))


# Example use
with timethis('counting'):
    n = 10000000
    while n > 0:
        n -= 1
