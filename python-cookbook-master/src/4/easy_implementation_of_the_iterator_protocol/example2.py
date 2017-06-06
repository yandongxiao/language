#! /usr/bin/env python3
# encoding: utf-8

# example.py
#
# Example of depth-first search using a generator

class Node:
    def __init__(self, value):
        self._value = value
        self._children = []

    def __repr__(self):
        return 'Node({!r})'.format(self._value)

    def add_child(self, node):
        self._children.append(node)

    def __iter__(self):
        yield self

    # 实现广度优先的方法，
    def width_first(self):
        yield self
        yield from self.loop()

    def loop(self):
        for c in self._children:
            yield c
        for c in self._children:
            # yield from 的真正作用就是允许生成器去调用另一个生成器
            yield from c.loop()

# Example
if __name__ == '__main__':
    root = Node(0)
    child1 = Node(1)
    child2 = Node(2)
    root.add_child(child1)
    root.add_child(child2)
    child1.add_child(Node(3))
    child1.add_child(Node(4))
    child2.add_child(Node(5))

    for ch in root.width_first():
        print(ch)
    # Outputs: Node(0), Node(1), Node(3), Node(4), Node(2), Node(5)
