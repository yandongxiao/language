#!/usr/bin/env python
# encoding: utf-8

# 参见：http://www.cnblogs.com/fnng/archive/2013/05/14/3078953.html
# 如何写一个迭代器
class Node(object):
    def __init__(self):
        self.buffer = []
        self.idx = 0

    def push(self, elmt):
        self.buffer.append(elmt)

    # 返回的对象需要包含next方法
    def __iter__(self):
        return self

    # NOTE: it is next not __next__
    def next(self):
        try:
            v = self.buffer[self.idx]
            self.idx += 1
            return v
        except IndexError:
            self.idx = 0
            # 注意产生异常的方法
            raise StopIteration


root = Node()
root.push(1)
root.push(2)
root.push(3)

for elmt in root:
    print elmt

for elmt in root:
    print elmt

print next(root, None)
print next(root, None)
print next(root, None)
print next(root, None)  # 不抛出异常的方法
