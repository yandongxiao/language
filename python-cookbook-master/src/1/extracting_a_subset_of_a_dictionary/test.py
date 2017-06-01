#!/usr/bin/env python
# encoding: utf-8

# not pprint
from pprint import pprint

prices = {
   'ACME': 45.23,
   'AAPL': 612.78,
   'IBM': 205.55,
   'HPQ': 37.20,
   'FB': 10.75
}

# 语法那里有不对
# dict is not iterable
#print {name:val for name, val in prices if val > 200}
# prepry print
pprint({name:val for name, val in prices.items() if val > 200})

tech_names = { 'AAPL', 'IBM', 'HPQ', 'MSFT' }

print {name:val for name, val in prices.items() if name in tech_names}
