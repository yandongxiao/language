#!/usr/bin/env python3
# encoding: utf-8

class sample1:
    __slots__ = ()

    def callme(self):
        print("sample1")
        return super().callme()

class sample2:
    __slots__ = ()

    def callme(self):
        print("sample2")
        return super().callme()

class me:
    def callme(self):
        print("callme")

class person(sample1, sample2, me):
    pass


p = person()
p.callme()
