#! /usr/bin/env python3
# encoding: utf-8

class Proxy(object):
    def __init__(self, obj):
        self._obj = obj

    # Delegate attribute lookup to internal obj
    # Called when an attribute lookup has not found the attribute in the usual places
    # Note that if the attribute is found through the normal mechanism, __getattr__() is not called.
    # See the __getattribute__() method below for a way to actually get total control in new-style classes.
    def __getattr__(self, name):
        return getattr(self._obj, name)

    # Delegate attribute assignment
    def __setattr__(self, name, value):
        if name.startswith('_'):
            super().__setattr__(name, value)    # Call object's __setattr__
        else:
            setattr(self._obj, name, value)


if __name__ == '__main__':
    class A:
        def __init__(self, x):
            self.x = x
        def spam(self):
            return 'A.spam'

    a = A(42)
    p = Proxy(a)
    assert p.x == 42
    assert p.spam() == "A.spam"

    p.x = 37
    assert p.x == 37
    assert a.x == 37

    p._a = 100
    # _a 是实例对象p的一个属性，不会调用__getattr__方法
    assert p._a == 100
