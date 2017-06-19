#!/usr/bin/env python3
# encoding: utf-8

class Base:
    def __init__(self, name):
        print("BASE")
        self.name = name

class Extend(Base):
    pass

# 虽然没有显式地定义Extentd的__init__方法，但是系统貌似会自动生成一个
# def __init__(self, name):
#     super().__init__(name)
e = Extend("bob")
print(e.__dict__)
print(e.name)
