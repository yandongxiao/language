#!/usr/bin/env python
# encoding: utf-8

class Node(object):
    def __init__(self, val):
        self._val = val
        self._child = []

    # __expr__ 与 __str__ 的区别
    # __str__ 是这里需要的方法，即print Node(1)输出对象的字符串形式
    # 没有__expr__, 正确的是 __repr__
    def __repr__(self):
        return "Node(" + str(self._val) + ")"

    def add_child(self, node):
        self._child.append(node)

    def __iter__(self):
        return iter(self._child)

root = Node(0)
n1 = Node(1)
n2 = Node(2)
root.add_child(n1)
root.add_child(n2)

for n in root:
    print n
