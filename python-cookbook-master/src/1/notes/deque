#! /usr/bin/python

from collections import deque

# a = deque(5)  # error.
a = deque(maxlen=5)

a.extend([1,2,3,4,5])
assert list(a) == [1,2,3,4,5]

a.append(9)
assert list(a) == [2,3,4,5,9]

a.appendleft(8)
assert list(a) == [8,2,3,4,5]

a.pop()
assert list(a) == [8,2,3,4]

a.popleft()
assert list(a) == [2,3,4]
