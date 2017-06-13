#!/usr/bin/env python3
# encoding: utf-8

# bottom 没有提供默认的值
# 这就要求调用者必须提供参数值，并且要以关键字参数的形式提供
def argv(first, *rest, bottom):
    m = float(first+sum(rest)) / (1 + len(rest))
    m = bottom if bottom < m else m
    return m

print(argv(1, 2, 3, 4, bottom=1))
print(argv(1, 2, 3, 4, bottom=20))


# 这里虽然有*
# 但是它不消费任何实参, 所以 recv(1,2)抛出了异常
def recv(first, *, block = False):
    print(first, block)

recv(1)
try:
    recv(1,2)
except TypeError as e:
    print(e)
recv(1, block=True)
