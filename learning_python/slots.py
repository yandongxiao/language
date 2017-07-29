#!/usr/bin/env python3
# encoding: utf-8

# 貌似没有什么问题呀

class Base:
    def __init__(self, name):
        print("BASE")
        #self.name = name
        self.__dict__.update({"name": name})
        self.vlaue = 10

class Extend(Base):
    __slots__ = ()  # 是无法限制基类的

e = Extend("bob")
print(e.__dict__)
print(e.name)
print(e.vlaue)
