#! /usr/bin/python
# encoding: utf-8

# Examples of different ways to filter data

mylist = [1, 4, -5, 10, -7, 2, 3, -1]

# 列表推导
# All positive values
pos = [n for n in mylist if n > 0]
print(pos)

# All negative values
neg = [n for n in mylist if n < 0]
print(neg)

# Negative values clipped to 0
neg_clip = [n if n > 0 else 0 for n in mylist]
print(neg_clip)

# Positive values clipped to 0
pos_clip = [n if n < 0 else 0 for n in mylist]
print(pos_clip)

# generator
print "max == %d" % max(n if n > 0 else 0 for n in mylist)

# Compressing example
addresses = [
    '5412 N CLARK',
    '5148 N CLARK',
    '5800 E 58TH',
    '2122 N CLARK',
    '5645 N RAVENSWOOD',
    '1060 W ADDISON',
    '4801 N BROADWAY',
    '1039 W GRANVILLE',
]

counts = [ 0, 3, 10, 4, 1, 7, 6, 1]

from itertools import compress

more5 = [n > 5 for n in counts ]    # more 是一个列表
a = list(compress(addresses, more5))
print(a)

b = [y for x,y in zip(counts, addresses) if x > 5 ]
print (b)

# compress更好的地方在于，它不需要构建新的迭代对象；
# 此处filter的输出，可能并非是自己所希望的
print filter(lambda x: x[0] > 5, zip(counts, addresses))

# filter函数创建了一个迭代器, filter用于创建复杂的过滤规则
values = ['1', '2', '-3', '-', '4', 'N/A', '5']
def is_int(val):
    try:
        x = int(val)
        return True
    except ValueError:
        return False
ivals = list(filter(is_int, values))
print(ivals)
