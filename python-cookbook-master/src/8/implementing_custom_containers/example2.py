#! /usr/bin/env python3
# encoding: utf-8

import collections

class Items(collections.MutableSequence):
    def __init__(self, initial=None):
        self._items = initial if initial is not None else []

    def __getitem__(self, index):
        return self._items[index]

    def __setitem__(self, index, value):
        self._items[index] = value

    def __delitem__(self, index):
        del self._items[index]

    def insert(self, index, value):
        self._items.insert(index, value)

    def __len__(self):
        return len(self._items)

    def __eq__(self, items):
        return self._items == items

if __name__ == '__main__':
    oa = [1, 2, 3]
    a = Items(oa)
    assert len(a) == 3
    a.append(4)
    a.append(2)
    assert oa == a
    assert a == [1, 2, 3, 4, 2]
    a.remove(3) # 删除第三个元素
    assert a == [1, 2, 4, 2]
