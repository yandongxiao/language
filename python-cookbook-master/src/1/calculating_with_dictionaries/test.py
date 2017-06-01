#!/usr/bin/env python
# encoding: utf-8


prices = {
   'ACME': 45.23,
   'BBBB': 45.23,
   'AAAA': 45.23,
   'AAPL': 612.78,
   'IBM': 205.55,
   'HPQ': 37.20,
   'FB': 10.75
}

print max(zip(prices.values(), prices.keys()))
print min(zip(prices.values(), prices.keys()))

for price, name in tuple(sorted(zip(prices.values(), prices.keys()))):
    print price, name
