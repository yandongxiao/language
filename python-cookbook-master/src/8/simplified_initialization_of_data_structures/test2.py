#!/usr/bin/env python3
# encoding: utf-8

# 貌似没有什么问题呀

class Base:
    def __init__(self, name):
        print("BASE")
        #self.name = name
        self.__dict__.update({"name": name})

class Extend(Base):
    __slots__ = ()

e = Extend("bob")
print(e.__dict__)
print(e.name)
