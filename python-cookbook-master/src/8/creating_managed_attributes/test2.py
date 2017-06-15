#!/usr/bin/env python3
# encoding: utf-8

class Person:
    def __init__(self, first_name):
        self.first_name= first_name

    def get_first_name(self):
        return self._first_name     # 任何方法都可以定义新的属性

    def set_first_name(self, val):
        if not isinstance(val, str):
            raise TypeError("first_name except a string val")
        self._first_name = val

    def del_first_name(self):
        del self._first_name

    # first_name 本身是一个描述符
    # 描述符的三个方法, __get__, __set__, __del__就是对象的property的三个参数
    first_name = property(get_first_name, set_first_name, del_first_name)

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
