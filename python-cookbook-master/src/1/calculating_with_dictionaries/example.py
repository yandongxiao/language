#!/usr/bin/env python
# encoding: utf-8

"""
    Find the max/min value in a dictory.
"""

# Find min and max price
# 比较的问题：
#     https://stackoverflow.com/questions/3270680/how-does-python-compare-string-and-int
#     1. Objects of different types except numbers are ordered by their type names
#     2. when you order a numeric and a non-numeric type, the numeric type comes first, 5 < {}


# NOTE
# prices.keys() 和 prices.values() 是两个独立的sequence
# 但是{ prices.keys()[i] : prices.values()[i] } 就是prices的一个元素

PRICES = {
    'ACME': 45.23,
    'BBBB': 45.23,
    'AAAA': 45.23,
    'AAPL': 612.78,
    'IBM': 205.55,
    'HPQ': 37.20,
    'FB': 10.75
}

# method-1
print max(PRICES, key=lambda k: PRICES[k])
print min(PRICES, key=lambda k: PRICES[k])
print sorted(PRICES, key=lambda k: PRICES[k])


# method-2
print max(PRICES.items(), key=lambda item: item[1])
print min(PRICES.items(), key=lambda item: item[1])
print sorted(PRICES.items(), key=lambda item: item[1])


# method-3
# 排序时比较的对象是一个含有两个元素的元组
print max(zip(PRICES.values(), PRICES.keys()))
print min(zip(PRICES.values(), PRICES.keys()))
print sorted(zip(PRICES.values(), PRICES.keys()))
