#! /usr/bin/python
# encoding: utf-8

# example.py
# Example of calculating with dictionaries

prices = {
   'ACME': 45.23,
   'BBBB': 45.23,
   'AAAA': 45.23,
   'AAPL': 612.78,
   'IBM': 205.55,
   'HPQ': 37.20,
   'FB': 10.75
}

# Find min and max price
# 比较的问题：
#     https://stackoverflow.com/questions/3270680/how-does-python-compare-string-and-int
#     1. Objects of different types except numbers are ordered by their type names
#     2. when you order a numeric and a non-numeric type, the numeric type comes first, 5 < 'foo', 5 < {}
#     3. When you order two incompatible types where neither is numeric, they are ordered by the alphabetical order of their typenames,
#        [1, 2] > 'foo'   # 'list' < 'str'
#
# prices.keys() 和 prices.values() 是两个独立的sequence，但是{ prices.keys()[i] : prices.values()[i] } 就是prices的一个元素
# NOTE: zip() 函数创建的是一个只能访问一次的迭代器。
min_price = min(zip(prices.values(), prices.keys()))
max_price = max(zip(prices.values(), prices.keys()))
print('min price:', min_price)
print('max price:', max_price)

print('sorted prices:')
prices_sorted = sorted(zip(prices.values(), prices.keys()))
for price, name in prices_sorted:   # seq接收数据的方法
    print('    ', name, price)
