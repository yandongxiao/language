#! /usr/bin/env python3
# encoding: utf-8

# 这是一个描述符
# class String 提供了一个对name的值的类型检查的功能
class String:
    def __init__(self, name):
        self.name = name

    def __get__(self, instance, cls):
        if instance is None:
            return self
        return instance.__dict__[self.name]

    def __set__(self, instance, value):
        if not isinstance(value, str):
            raise TypeError('Expected a string')
        instance.__dict__[self.name] = value


class Person:
    name = String('name')
    def __init__(self, name):
        self.name = name

class SubPerson(Person):
    @property
    def name(self):
        print('Getting name')
        return super().name

    @name.setter
    def name(self, value):
        print('Setting name to', value)
        super(SubPerson, SubPerson).name.__set__(self, value)

    @name.deleter
    def name(self):
        print('Deleting name')
        super(SubPerson, SubPerson).name.__delete__(self)

# NOTE: NOTE: 以下方式是不支持的哟
# 'String' object has no attribute 'getter'
#class SubPerson2(Person):
#    @Person.name.getter
#    def name(self):
#        print('SubPerson2 Getting name')
#        return super().name

if __name__ == '__main__':
   a = Person('Guido')
   print(a.name)
   a.name = 'Dave'
   print(a.name)
   try:
       a.name = 42
   except TypeError as e:
       print(e)

