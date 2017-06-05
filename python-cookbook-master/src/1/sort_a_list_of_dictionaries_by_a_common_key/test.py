#!/usr/bin/env python
# encoding: utf-8



rows = [
    {'fname': 'Brian', 'lname': 'Jones', 'uid': 1003},
    {'fname': 'David', 'lname': 'Beazley', 'uid': 1002},
    {'fname': 'John', 'lname': 'Cleese', 'uid': 1001},
    {'fname': 'Big', 'lname': 'Jones', 'uid': 1004}
]

rows.sort(key=lambda s: s['fname'])
print rows

rows.sort(key=lambda s: s['uid'])
print rows

rows.sort(key=lambda s: (s['lname'], s['fname']))
print rows

class itemgetter(object):
    def __init__(self, item, *items):
        if items:
            # 这个放在func内部为什么就不可以
            items = (item, ) + items
            def func(obj):
                return tuple(obj[i] for i in items)
        else:
            def func(obj):
                # tuple(3) 有语法错误的
                return obj[item]
        self.func = func


    def __call__(self, obj):
        self.func(obj)

rows.sort(key=itemgetter('fname'))
print rows

rows.sort(key=itemgetter('uid'))
print rows

rows.sort(key=itemgetter('lname', 'fname'))
print rows
