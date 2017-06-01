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

print heapq.nsmallest(3, portfolio, lambda s: s['price'])
print heapq.nlargest(3, portfolio, lambda s: s['price'])
