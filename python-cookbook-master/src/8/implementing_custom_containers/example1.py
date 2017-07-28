#! /usr/bin/env python3
# encoding: utf-8

'''
collections 中定义了很多的容器基类，当你希望自定义自己的容器时，应该考虑从colelctions的某个基类中继承
'''

import collections
import bisect


class SortedItems(collections.Sequence):    # collections 像是一个抽象基类一样
    def __init__(self, initial=None):
        self._items = sorted(initial) if initial is not None else []

    # Required sequence methods
    def __getitem__(self, index):
        return self._items[index]

    def __len__(self):
        return len(self._items)

    # Method for adding an item in the right location
    def add(self, item):
        bisect.insort(self._items, item)

    def __eq__(self, item):
        return self._items == item


if __name__ == '__main__':
   items = SortedItems([5, 1, 3])
   assert items == [1, 3, 5]
   assert items[-1] == 5        # index 支持负数形式
   items.add(2)
   items.add(-10)
   assert items == [-10, 1, 2, 3, 5]
   assert 3 in items
   assert len(items) == 5
