#!/usr/bin/env python
# encoding: utf-8

class Node(object):
    def __init__(self):
        self.buffer = []
        self.idx = 0

    def push(self, elmt):
        self.buffer.append(elmt)

    def __iter__(self):
        # 将迭代操作代理到内部的容器上面
        # 传递迭代请求到内部的容器
        # iter(s) 只是简单的通过调用 s.__iter__() 方法来返回对应的迭代器对象
        # 就跟 len(s) 会调用 s.__len__() 原理是一样的
        return iter(self.buffer)


root = Node()
root.push(1)
root.push(2)
root.push(3)

for elmt in root:
    print elmt
