#!/usr/bin/env python3
# encoding: utf-8

class Person:
    def __init__(self, name):
        self.name = name

    @property
    def name(self):
        return self._name

    @name.setter
    def name(self, val):
        if not isinstance(val, str):
            raise TypeError("expect a string")
        self._name = val

    @name.deleter
    def name(self):
        del self._name

p = Person("jack")
try:
    p.name = 10
except TypeError as e:
    print(e)
print(p.name)
print("==================")

class SubPerson1(Person):
    def __init__(self, name):
        super().__init__(name)

    @property
    def name(self):
        print("SubPerson1 get name")
        return super().name

    @name.setter
    def name(self, val):
        print("SubPerson1 set name")
        # 注意是通过类的方式来访问name的
        super(SubPerson1, SubPerson1).name.__set__(self, val)

    @name.deleter
    def name(self, val):
        print("SubPerson1 delete name")
        super(SubPerson1, SubPerson1).name.__delete__(self)


p = SubPerson1("jack")
try:
    p.name = 10
except TypeError as e:
    print(e)
print(p.name)
print("==================")

class SubPerson2(SubPerson1):
    def __init__(self, name):
        super().__init__(name)

    @SubPerson1.name.getter
    def name(self):
        print("SubPerson2 get name")
        return super().name

p = SubPerson2("jack")
try:
    p.name = 10
except TypeError as e:
    print(e)
print(p.name)
