#!/usr/bin/python
# example.py
#
# Unpacking of tagged tuples of varying sizes

records = [
     ('foo', 1, 2),
     ('bar', 'hello'),
     ('foo', 3, 4),
]

def do_foo(x, y):
    print('foo', x, y)

def do_bar(s):
    print('bar', s)

for tag, *args in records:  # the type of args is list!!
    if tag == 'foo':
        do_foo(*args)
        # 由调用者决定是否将list进行展开
        # missing 1 required positional argument: 'y'
        # do_foo(args)
    elif tag == 'bar':
        do_bar(*args)
        do_bar(args)
