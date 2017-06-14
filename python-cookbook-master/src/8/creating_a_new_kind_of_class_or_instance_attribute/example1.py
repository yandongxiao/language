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


# 默认对属性的访问控制是从对象的字典里面(__dict__)中获取(get), 设置(set)和删除(delete)它
# 举例来说，a.x 的查找顺序是, a.__dict__['x'] , 然后 type(a).__dict__['x'] , 然后找 type(a) 的父类
# NOTE: 如果查找到的值是一个描述器, Python就会调用描述器的方法来重写默认的控制行为
class Point:
    x = Integer('x')
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

    # NOTE: x的值并没有新的实例的产生而被更改
    # 请查看Integer类实现
    Point(4, 5)
    print(p.x)
