#!/usr/bin/env python
# encoding: utf-8

from itertools import dropwhile

# 直到找到第一个大于等于5的元素，然后遍历后续的元素
for k in dropwhile(lambda x: x<5, [4,5,6,3,8]):
    print k
