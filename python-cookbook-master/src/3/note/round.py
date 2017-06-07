#!/usr/bin/env python3
# encoding: utf-8

# python2当中采用的是真正的四舍五入
# 当一个值刚好在两个边界的中间的时候， round 函数返回离它最近的偶数
# python3当中以下两个值返回的都是2.0
print(round(1.5, 0))
print(round(2.5, 0))

# 也会进行舍入运算
x = 1.23456
print(format(x, '0.2f'))
print(format(x, '0.3f'))
