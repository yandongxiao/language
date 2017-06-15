#!/usr/bin/env python3
# encoding: utf-8

class Person:
    def __init__(self, first_name):
        self.first_name= first_name

    @property
    def first_name(self):
        return self._first_name     # 任何方法都可以定义新的属性

    @first_name.setter
    def first_name(self, val):
        if not isinstance(val, str):
            raise TypeError("first_name except a string val")
        self._first_name = val

    @first_name.deleter
    def first_name(self):
        del self._first_name


if __name__ == '__main__':
   a = Person('Guido')
   print(a.first_name)
   a.first_name = 'Dave'
   print(a.first_name)
   try:
       a.first_name = 42
   except TypeError as e:
       print(e)

   del a.first_name
