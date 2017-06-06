#!/usr/bin/env python
# encoding: utf-8

class Node(object):
    def __init__(self):
        self.buffer = []
        self.idx = 0

    def push(self, elmt):
        self.buffer.append(elmt)

    def __iter__(self):
        return iter(self.buffer)


root = Node()
root.push(1)
root.push(2)
root.push(3)

for elmt in root:
    print elmt
