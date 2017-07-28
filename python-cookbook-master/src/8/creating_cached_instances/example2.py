#! /usr/bin/env python
# encoding: utf-8

import weakref

class CachedSpamManager:
    def __init__(self):
        self._cache = weakref.WeakValueDictionary()
    def get_spam(self, name):
        if name not in self._cache:
            # 下面的错误在于
            # 由于是弱引用Spam(name)会被垃圾回收
            # return语句返回是产生KeyError
            # self._cache[name] = Spam(name)
            # return self._cache[name]

            s = Spam(name)
            self._cache[name] = s
        else:
            s = self._cache[name]
        return s    # 强引用

class Spam:
    # as a class attribute
    manager = CachedSpamManager()
    def __init__(self, name):
        self.name = name

def get_spam(name):
    return Spam.manager.get_spam(name)

if __name__ == '__main__':
    a = get_spam('foo')
    b = get_spam('bar')
    print('a is b:', a is b)
    c = get_spam('foo')
    print('a is c:', a is c)
