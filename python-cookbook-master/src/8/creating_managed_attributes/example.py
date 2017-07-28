#! /usr/bin/env python3
# encoding: utf-8

class Person:
    # 底层存储的对象名称实际上是_first_name
    # self.first_name = first_name实际上是为了触发setter函数的执行
    def __init__(self, first_name):
        self.first_name = first_name        # 调用first_name的set方法

    # Getter function
    @property
    def first_name(self):
        return self._first_name

    # Setter function
    @first_name.setter
    def first_name(self, value):
        if not isinstance(value, str):
            raise TypeError('Expected a string')
        self._first_name = value

    @first_name.deleter
    def first_name(self):
        raise RuntimeError("not allowed")


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
