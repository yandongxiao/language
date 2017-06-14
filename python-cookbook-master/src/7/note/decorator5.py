#!/usr/bin/env python
# encoding: utf-8

from functools import wraps

def decorate_C(function):
    # 修正
    # w = wraps(function)
    # wrap_function = w(wrap_function)
    @wraps(function)
    def wrap_function(*args, **kwargs):
        str = 'Hello!'
        #args.insert(1, str)
        args = (args[0],) + (str,) + args[1:]
        return function(*args, **kwargs)
    return wrap_function

class Printer:
    # 我们可以通过一个普通的装饰器，为一个类方法做装饰
    # 这里是注入一个参数
    @decorate_C
    def print_message(self, str, *args, **kwargs):
        print(str)

p = Printer()
p.print_message(1)

# 如果没有装饰器的存在，返回值应该是print_message

print p.print_message.__name__
