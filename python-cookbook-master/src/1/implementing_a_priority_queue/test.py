#!/usr/bin/env python
# encoding: utf-8

from heapq import heappush
from heapq import heappop

persons = []

heappush(persons, "jack")
heappush(persons, "john")
heappush(persons, "alice")
heappush(persons, "bob")

for p in persons:
    print p

class PriorityPerson(object):
    def __init__(self):
        self.list = []

    def push(self, name, priority):
        heappush(self.list, (-priority, name))

    def pop(self):
        _, name = heappop(self.list)
        return name

persons = PriorityPerson()

persons.push("alice", 1)
persons.push("bob", 10)
persons.push("cindy", 5)
persons.push("dav", 6)


print persons.pop()
print persons.pop()
print persons.pop()
print persons.pop()
