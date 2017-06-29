#! /usr/bin/env python3
# encoding: utf-8

class typed_property(object):
    def __init__(self, name, expect_type):
        self.name = "_" + name
        self.expect_type = expect_type

    def __get__(self, instance, owner):
        if instance is None:
            return None
        return getattr(instance, self.name)

    def __set__(self, instance, value):
        if not isinstance(value, self.expect_type):
            raise TypeError('{} must be a {}'.format(self.name[1:], self.expect_type))
        setattr(instance, self.name, value)

# Example use
class Person:
    name = typed_property('name', str)
    age = typed_property('age', int)
    def __init__(self, name, age):
        self.name = name
        self.age = age

if __name__ == '__main__':
    p = Person('Dave', 39)
    p.name = 'Guido'
    try:
        p.age = 'Old'
    except TypeError as e:
        print(e)

