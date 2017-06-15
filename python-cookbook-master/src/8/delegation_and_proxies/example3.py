#! /usr/bin/env python
# encoding: utf-8

class ListLike:
    def __init__(self):
        self._items = []
    def __getattr__(self, name):
        return getattr(self._items, name)

    # Added special methods to support certain list operations
    # __getattr__对于双下划线开始和结尾的方法是不能用的，需要一个个去重定义
    def __len__(self):
        return len(self._items)
    def __getitem__(self, index):
        return self._items[index]
    def __setitem__(self, index, value):
        self._items[index] = value
    def __delitem__(self, index):
        del self._items[index]

if __name__ == '__main__':
    a = ListLike()
    a.append(2)
    a.insert(0, 1)
    a.sort()
    print(len(a))
    print(a[0])

