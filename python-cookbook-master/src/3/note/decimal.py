#!/usr/bin/env python3
# encoding: utf-8

# NOTE：这个Decimal竟然不存在，好奇怪
from decimal import Decimal

a = 4.2
b = 2.1
# python2 返回的是6.3
# python3 返回的是6.300000000000001
print(a+b)
print(a+b == 6.3)
