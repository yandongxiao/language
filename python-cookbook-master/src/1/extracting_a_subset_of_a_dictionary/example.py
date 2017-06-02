#! /usr/bin/python
# encoding: utf-8

# example of extracting a subset from a dictionary
from pprint import pprint

prices = {
   'ACME': 45.23,
   'AAPL': 612.78,
   'IBM': 205.55,
   'HPQ': 37.20,
   'FB': 10.75
}

# Make a dictionary of all prices over 200
p1 = { key:value for key, value in prices.items() if value > 200 }

print("All prices over 200")
pprint(p1)
print(p1)

# Make a dictionary of tech stocks
tech_names = { 'AAPL', 'IBM', 'HPQ', 'MSFT' }
p2 = { key:value for key,value in prices.items() if key in tech_names }

# 大多数情况下字典推导能做到的，通过创建一个元组序列然后把它传给 dict() 函数也能实现
p3 = dict((key, value) for key, value in prices.items() if key in tech_names)

print("All techs")
print(p2)
print("-----------")
print(p3)
