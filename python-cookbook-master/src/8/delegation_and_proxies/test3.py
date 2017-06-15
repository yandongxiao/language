#!/usr/bin/env python3
# encoding: utf-8

class ListLike:
    def __init__(self):
        self._obj = []

    def __getattr__(self, key):
        return getattr(self._obj, key)

    def __len__(self):
        return len(self._obj)

    def __getitem__(self, i):
        return self._obj[i]

    def __setitem__(self, i, v):
        self._obj[i] = v

    def __delitem__(self, i):
        del self._obj[i]

if __name__ == '__main__':
    a = ListLike()
    a.append(2)
    a.insert(0, 1)
    a.sort()
    print(len(a))
    print(a[0])

