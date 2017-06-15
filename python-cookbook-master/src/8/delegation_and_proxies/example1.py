#! /usr/bin/env python
# encoding: utf-8

class A:
    def spam(self, x):
        print('A.spam')

    def foo(self):
        print('A.foo')

class B:
    def __init__(self):
        self._a = A()

    def bar(self):
        print('B.bar')

    # 只有当属性不存在时，该方法才会被调用
    def __getattr__(self, name):
        return getattr(self._a, name)

if __name__ == '__main__':
    b = B()
    b.bar()
    b.spam(42)
