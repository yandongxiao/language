#! /usr/bin/env python3
# encoding: utf-8

# @abstractmethod 还能注解静态方法、类方法和 properties
# 你只需保证这个注解紧靠在函数定义前即可
from abc import ABCMeta, abstractmethod

class A(metaclass=ABCMeta):
    @property
    @abstractmethod     # abstractmethod紧靠着方法名称
    def name(self):
        pass

    @name.setter
    @abstractmethod
    def name(self, value):
        pass

    @classmethod
    @abstractmethod
    def method1(cls):
        pass

    @staticmethod
    @abstractmethod
    def method2():
        pass

class B(A):
    @property
    def name(self):
        print("get name")
        return self._name

    @name.setter
    def name(self, name):
        print("set name")
        self._name = name

    @classmethod
    def method1(cls):
        print("class method1")

    @staticmethod
    def method2():
        print("static method2")

b = B()
b.name = "jack"
print(b.name)
B.method1()
B.method2()
