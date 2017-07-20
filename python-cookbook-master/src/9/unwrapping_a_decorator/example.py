#! /usr/bin/env python3
# encoding: utf-8

# Example of unwrapping a decorator

from functools import wraps

def decorator1(func):
    @wraps(func)
    def wrapper(*args, **kwargs):
        print('Decorator 1')
        return func(*args, **kwargs)
    return wrapper

def decorator2(func):
    @wraps(func)
    def wrapper(*args, **kwargs):
        print('Decorator 2')
        return func(*args, **kwargs)
    return wrapper

# 注意先执行decorator1的print语句
# 因为print语句在func之前
@decorator1
@decorator2
def add(x, y):
    return x + y

# Calling wrapped function
print(add(2,3))

# Calling original function
# __wrapped__特殊方法只在python3当中才有
print(add.__wrapped__.__wrapped__(2, 3))
