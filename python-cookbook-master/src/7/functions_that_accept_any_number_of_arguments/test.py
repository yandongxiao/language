#!/usr/bin/env python
# encoding: utf-8

#
# NOTE:
# 1. 一个*参数只能出现在函数定义中最后一个位置参数后面
# 2.  **参数只能出现在最后一个参数。
# 3. a 和 b 函数后面使用参数y，要求调用者必须使用关键字参数来传递参数
def a(x, *args, y):
        pass

def b(x, *args, y, **kwargs):
        pass

# 接收任意数量的参数
# NOTE: rest 是元组，不是列表
def agv(first, *rest):
    return float(first+sum(rest)) / (len(rest)+1)

print agv(1, 2, 3, 4)
print agv(1)

# 接收任意数量的关键字参数
# NOTE: 列表推导，看来只要是表达式就可以
def make_element(name, value, **attrs):
    attrs_str = ["%s=%s" % item for item in attrs.items()]
    attr = ' '.join(attrs_str)
    element = '<{name} {attrs}>{value}</{name}>'.format(
                name = name,
                value = value,
                attrs = attr
                )
    return element

print(make_element('item', 'Albatross', size='large', quantity=6))
print(make_element('p','<spam>'))
