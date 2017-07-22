#!/usr/bin/env python
# encoding: utf-8

nums = [1, 5, 2, 1, 9, 1, 5, 10]

a = [
    {'x': 2, 'y': 3},
    {'x': 1, 'y': 4},
    {'x': 2, 'y': 3},
    {'x': 2, 'y': 3},
    {'x': 10, 'y': 15}
]

# method - 1
# 因为item需要被放到set当中，所以它必须是hashable的
# 比如字典就不是hashable的
# comparable 与 hashable 不是一个概念，hashable一般要求对象是不可变对象
s = set()
for num in nums:
    if not num in s:
        s.add(num)
        print num,
print

# method - 2
# 使用list解决了hashable的问题，但是时间复杂度太高
s = list()
for num in a:
    if not num in s:
        s.append(num)
        print num,
print

# method - 3
# 降低了时间复杂度，同时可以以字典作为列表的元素
# 要求：列表中只有x，y元素
s = set()
key = lambda elmt: (elmt['x'], elmt['y'])
for elmt in a:
    k = key(elmt)
    if k not in s:
        s.add(k)
        print elmt
