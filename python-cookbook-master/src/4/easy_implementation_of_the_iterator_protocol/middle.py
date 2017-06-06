#!/usr/bin/env python3
# encoding: utf-8

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

    def middle_sort(self):
        if self._children:
            yield from self._children[0].middle_sort()
        yield self
        for i in range(1, len(self._children)):
            yield from self._children[i].middle_sort()

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

    for ch in root.middle_sort():
        print(ch)
    # Outputs: Node(0), Node(1), Node(3), Node(4), Node(2), Node(5)
