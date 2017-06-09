#! /usr/bin/env python3
# encoding: utf-8

# 这又是python3的新特性
# Example of managed attributes via properties

class Person:
    def __init__(self, first_name):
        self.first_name = first_name

    # Getter function
    def get_first_name(self):
        return self._first_name

    # Setter function
    def set_first_name(self, value):
        if not isinstance(value, str):
            raise TypeError('Expected a string')
        self._first_name = value

    def delete_first_name(self):
        raise RuntimeError("not allowed")

    first_name = property(get_first_name, set_first_name, delete_first_name)

if __name__ == '__main__':
   a = Person('Guido')
   print(a.first_name)
   a.first_name = 'Dave'
   print(a.first_name)
   try:
       a.first_name = 42
   except TypeError as e:
       print(e)
