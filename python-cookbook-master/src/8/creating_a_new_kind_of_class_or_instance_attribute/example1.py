#! /usr/bin/env python3
# encoding: utf-8


# 描述器类, 注意不是装饰器
# 描述器可实现大部分Python类特性中的底层魔法, 如@classmethod，@staticmethod等
class Integer:
    def __init__(self, name):
        self.name = name

    # NOTE: 注意与__getattr__进行区分
    # 注意这里有三个参数
    # instance==p, cls==Point
    def __get__(self, instance, cls):
        # 用Point类来访问时，Point.x 此时instance == None
        # NOTE：实例变量和类变量的区别
        if instance is None:
            return self
        else:
            return instance.__dict__[self.name]

    # NOTE: 注意与__setattr__进行区分
    def __set__(self, instance, value):
        if not isinstance(value, int):
            raise TypeError('Expected an int')
        instance.__dict__[self.name] = value

    def __delete__(self, instance):
        del instance.__dict__[self.name]


class Point:
    x = Integer('x')    # 定义的类变量
    y = Integer('y')
    def __init__(self, x, y):
        self.x = x  # 调用了Integer类的__setter__方法
        self.y = y


if __name__ == '__main__':
    # 对实例v的操作不会触发__get__和__set__的操作
    # 只有被当作其他类的成员属性时，__get__ 和 __set__ 方法才会起作用
    v = Integer("age")
    v.age = 10      # NOTE: 并没有触发__set__操作
    print(v.age)    # NOTE: 并没有触发__get__操作
    print("===================")

    p = Point(2, 3) # 两次set操作
    print(p.x)      # 一次get操作
    p.y = 5         # 一次set
    try:
        p.x = 2.3   # 一次set操作
    except TypeError as e:
        print(e)

    p2 = Point(100, 200)
    print (p.x)
