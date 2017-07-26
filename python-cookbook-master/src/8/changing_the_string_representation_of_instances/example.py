#!/usr/bin/env python
# encoding: utf-8

class Point:
    def __init__(self, x, y):
        self.x = x
        self.y = y

    # __repr__() 方法返回一个实例的代码表示形式，通常用来重新构造这个实例
    # 内置的 repr() 函数返回这个字符串
    # NOTE: __repr__() 生成的文本字符串标准做法是需要让 eval(repr(x)) == x 为真
    # 如果实在不能这样子做，应该创建一个有用的文本表示，并使用 < 和 > 括起来。
    # <_io.TextIOWrapper name='file.dat' mode='r' encoding='UTF-8'>
    def __repr__(self):
        return "Point(%d, %d)" % (self.x, self.y)

    # print, str 一个类对象就会执行该方法
    # 如果 __str__() 没有被定义，那么就会使用 __repr__() 来代替输出
    def __str__(self):
        return self.__repr__()


p = Point(3,4)
print eval(repr(p))
print p
