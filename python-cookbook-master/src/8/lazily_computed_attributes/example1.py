#! /usr/bin/env python
# encoding: utf-8

import math

class lazyproperty:
    def __init__(self, func):
        self.func = func

    def __get__(self, instance, cls):
        if instance is None:
            return self
        else:
            value = self.func(instance)
            # 设置实例的同名属性
            # 实例的属性要比类对象的属性优先级更高, 所以下次缓存起来了
            setattr(instance, self.func.__name__, value)
            return value

from functools import wraps

def lazyproperty2(func):
    @wraps(func)
    def new_func(self, *args, **kwargs):
        val = func(self, *args, **kwargs)
        setattr(self, func.__name__, val)
        return val
    return new_func


class Circle:
    def __init__(self, radius):
        self.radius = radius

    # 修饰符放在方法上也是可以的
    # area = lazyproperty(area)
    # NOTE: 以上调用正好符合了描述符的应用场景
    @lazyproperty2
    def area(self):
        print('Computing area')
        return math.pi * self.radius ** 2

    @lazyproperty2
    def perimeter(self):
        print('Computing perimeter')
        return 2 * math.pi * self.radius

c = Circle(1)
print(c.area())
print(c.perimeter())
print(c.area)
print(c.perimeter)
