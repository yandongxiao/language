#! /usr/bin/env python
# encoding: utf-8

"""
    Implementing a priority queue
"""

__all__ = ['PriorityQueue']

import heapq


class PriorityQueue(object):
    """List that has priority"""

    def __init__(self):
        self._queue = []
        self._index = 0

    def push(self, item, priority):
        """push an item with priority"""
        # heapq 本身并不支持key关键字，需要借助元组的特殊比较方式来实现
        heapq.heappush(self._queue, (-priority, self._index, item))
        self._index += 1

    def pop(self):
        """pop an item with leastest priority"""
        return heapq.heappop(self._queue)[-1]


q = PriorityQueue()
q.push('foo', 1)
q.push('bar', 5)
q.push('spam', 4)
q.push('grok', 1)

print("Should be bar:", q.pop())
print("Should be spam:", q.pop())
print("Should be foo:", q.pop())
print("Should be grok:", q.pop())
