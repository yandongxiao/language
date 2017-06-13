#!/usr/bin/env python3
# encoding: utf-8

# NOTE: rest 是一个列表
def avg(first, *rest):
    return float(first+sum(rest)) / (1+len(rest))

print(avg(1, 2, 3, 4))
print(avg(1))

# NOTE: 调用时callbak必须提供，而且以关键字形式
# 这是python3的特性
def avg(first, *rest, callback):
    val = float(first+sum(rest)) / (1+len(rest))
    callback(val)
avg(1, 2, 3, 4, callback=print)
avg(1, callback=print)

# 关键字参数
def print_elmt(**elmts):
    # elmts = ["%s:%s" % (e[0], e[1])  for e in elmts.items() ]
    # more better
    elmts = ["%s:%s" % e for e in elmts.items()]
    print(elmts)
print_elmt()
print_elmt(name="jack", age=10)
