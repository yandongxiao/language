#! /usr/bin/env python3
# encoding: utf-8

# example.py
#
# Find out what two dictionaries have in common

a = {
   'x' : 1,
   'y' : 2,
   'z' : 3
}

b = {
   'w' : 10,
   'x' : 11,
   'y' : 2
}

# 字典的 keys() 方法返回一个展现键集合的键视图对象。
# 键视图的一个很少被了解的特性就是它们也支持集合操作
# 可以直接使用键视图对象而不用先将它们转换成一个set
# 字典的 items() 方法返回的视图对象也支持集合操作
print('Common keys:', a.keys() & b.keys())
print('Keys in a not in b:', a.keys() - b.keys())
print('(key,value) pairs in common:', a.items() & b.items())
