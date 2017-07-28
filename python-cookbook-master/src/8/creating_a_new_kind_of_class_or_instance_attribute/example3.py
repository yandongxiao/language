#!/usr/bin/env python
# encoding: utf-8


class Integer(object):
    def __init__(self, name):
        self.name = name

    def __get__(self, instance, cls):
        print "__get__"
        if instance is None:
            return None
        else:
            return instance.__dict__[self.name]


class Point(object):
    x = Integer('x')    # 定义的类变量
    y = Integer('y')

    def __init__(self, x, y):
        self.x = x  # 调用了Integer类的__setter__方法
        self.y = y


if __name__ == "__main__":
    p1 = Point(1, 1)
    p2 = Point(2, 2)

    # 注意与Point.x.__get__(p1, Point) 的区别
    print Point.__dict__['x'].__get__(p1, Point)
    print Point.x

