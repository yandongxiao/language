#! /usr/bin/python
# encoding: utf-8

# example.py
#
# Some examples of using generators in arguments

# 当生成器表达式作为一个单独参数传递给函数时候的巧妙语法(你并不需要多加一个括号)
import os
files = os.listdir(os.path.expanduser('~'))
if any(name.endswith('.py') for name in files):
    print('There be python!')
else:
    print('Sorry, no python.')

# Output a tuple as CSV
s = ('ACME', 50, 123.45)
print(','.join(str(x) for x in s))

# Data reduction across fields of a data structure
portfolio = [
   {'name':'GOOG', 'shares': 50},
   {'name':'YHOO', 'shares': 75},
   {'name':'AOL', 'shares': 20},
   {'name':'SCOX', 'shares': 65}
]

min_shares = min(s['shares'] for s in portfolio)
print(min_shares)   # 只会输出20

min_shares = min(portfolio, key=lambda s: s['shares'])
print(min_shares)   # 输出列表中一个完整的元素
