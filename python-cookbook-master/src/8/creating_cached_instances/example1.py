#!/usr/bin/env python
# encoding: utf-8

# Simple example

class Spam:
    def __init__(self, name):
        self.name = name

# Caching support
# 在对象群组内部使用弱引用（即不会在引用计数中被计数的引用）有时能避免出现引用环，因此弱引用可用于解决循环引用的问题
# 弱引用，与强引用相对，是指不能确保其引用的对象不会被垃圾回收器回收的引用。
import weakref
_spam_cache = weakref.WeakValueDictionary()

def get_spam(name):
    if name not in _spam_cache:
        s = Spam(name)
        assert sys.getrefcount(s) == 2
        _spam_cache[name] = s
        assert sys.getrefcount(s) == 2
    else:
        assert sys.getrefcount(_spam_cache[name]) == 2
        s = _spam_cache[name]       # 注意这里返回的是一个强引用
        assert sys.getrefcount(_spam_cache[name]) == 3
    return s    # 这里返回一个强引用


import sys
if __name__ == '__main__':
    a = get_spam('foo')
    b = get_spam('bar')
    print('a is b:', a is b)
    c = get_spam('foo')
    print('a is c:', a is c)
