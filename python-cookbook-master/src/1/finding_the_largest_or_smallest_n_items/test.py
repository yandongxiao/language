#!/usr/bin/env python
# encoding: utf-8

import heapq

# dict 是无法比较大小的
portfolio = [
   {'name': 'IBM', 'shares': 100, 'price': 91.1},
   {'name': 'AAPL', 'shares': 50, 'price': 543.22},
   {'name': 'FB', 'shares': 200, 'price': 21.09},
   {'name': 'HPQ', 'shares': 35, 'price': 31.75},
   {'name': 'YHOO', 'shares': 45, 'price': 16.35},
   {'name': 'ACME', 'shares': 75, 'price': 115.65}
]

# 参数key的作用就是使用dict中的一个元素作为比较的对象
print heapq.nsmallest(3, portfolio, lambda s: s['price'])
portfolio.sort(key=lambda s: s['price'])
for i in range(0, 3):
    print portfolio[i]


print heapq.nlargest(3, portfolio, lambda s: s['price'])
portfolio.sort(key=lambda s: s['price'], reverse=True)
for i in range(0, 3):
    print portfolio[i]
