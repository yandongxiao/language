#!/usr/bin/env python
# encoding: utf-8

# method - 1
rows = [
    {'fname': 'Brian', 'lname': 'Jones', 'uid': 1003},
    {'fname': 'David', 'lname': 'Beazley', 'uid': 1002},
    {'fname': 'John', 'lname': 'Cleese', 'uid': 1001},
    {'fname': 'Big', 'lname': 'Jones', 'uid': 1004}
]

a1 = sorted(rows, key=lambda item: item['fname'])
a2 = sorted(rows, key=lambda item: item['uid'])
a3 = sorted(rows, key=lambda item: (item['uid'], item['fname']))

# method - 2
from operator import itemgetter
b1 = sorted(rows, key=itemgetter('fname'))
b2 = sorted(rows, key=itemgetter('uid'))
b3 = sorted(rows, key=itemgetter('uid', 'fname'))
assert(a1==b1)
assert(a2==b2)
assert(a3==b3)

# method - 3
# item is a tuple, you do not need to assign it.
class itemgetter:
    def __init__(self, item, *items):
        self.items = (item, ) + items
    def __call__(self, obj):
        return tuple(obj[x] for x in self.items)

c1 = sorted(rows, key=itemgetter('fname'))
c2 = sorted(rows, key=itemgetter('uid'))
c3 = sorted(rows, key=itemgetter('uid', 'fname'))
assert(a1==c1)
assert(a2==c2)
assert(a3==c3)
