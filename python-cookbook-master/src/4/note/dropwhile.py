#!/usr/bin/env python
# encoding: utf-8

l = [1, 2, 3, 4, -1, 5, 3, 8]

# 1
from itertools import dropwhile
for i in dropwhile(lambda s: s<5, l):
    print i

# 2
print [i for i in l if i>=5]

# 3

from itertools import islice

for i in islice(l, 5, None):
    print i
