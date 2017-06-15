#! /usr/bin/env python
# encoding: utf-8

import weakref

wvd = weakref.WeakValueDictionary()

class sample:
    def __init__(self, name):
        self.name = name

def get_sample(name):
    # 优化1
    # val = wvd.get(name, None)
    #if val is None:
    if name not in wvd:
        # 下面的错误在于
        # 由于是弱引用sample(name)会被垃圾回收
        # return语句返回是产生KeyError
        # wvd[name] = sample(name)
        # return wvd[name]

        s = sample(name)
        wvd[name] = s
        return s
    else:
        s = wvd[name]
        return s

if __name__ == "__main__":
    v1 = get_sample("foo")
    v2 = get_sample("bar")
    v3 = get_sample("foo")

    assert v1 is v3
    assert v1 is not v2


    # see http://www.jianshu.com/p/0cecea85ae3b
    s = sample("s")
    import sys
    assert 2 == sys.getrefcount(s)
    s1 = s
    assert 3 == sys.getrefcount(s)
    s2 = weakref.ref(s)
    assert 3 == sys.getrefcount(s)
    s3 = s2     # 注意返回的是一个弱引用
    assert 3 == sys.getrefcount(s3)


    s1 = sample("s")
    s2 = sample("s")
    assert s1 != s2     # 它们在内存当中是两块独立的内存
