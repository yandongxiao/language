#!/usr/bin/env python3
# encoding: utf-8

# 介绍内置装饰器
# 只有三个内置装饰器：staticmethod, classmethod, property

class A():
    @staticmethod
    def test_static():
        # 静态方法不需要self
        print("static")

    def test_normal(self):
        print("normal")

    @classmethod
    def test_class(cls):
        # 类方法的第一个参数是类型对象
        # 可以通过实例和类对象进行调用
        # 类方法需要额外的类变量cls，当有子类继承时，调用类方法传入的类变量cls是子类，而不是父类
        print("class", cls)

a = A()
A.test_static()
a.test_static()
a.test_normal()
a.test_class()

# property
class B():
    def __init__(self):
        self.__prop = 1
    @property
    def prop(self):
        print("call get")
        return self.__prop
    # 下面两种装饰器的语法好像只有在python3当中才有的
    @prop.setter
    def prop(self, value):
        print("call set")
        self.__prop = value
    @prop.deleter
    def prop(self):
        print("call del")
        del self.__prop

b = B()
b.prop
b.prop = 20
del b.prop
