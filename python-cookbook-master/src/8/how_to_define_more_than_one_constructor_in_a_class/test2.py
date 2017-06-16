#!/usr/bin/env python3
# encoding: utf-8

import time

class Date:
    def __init__(self, year, month, day):
        self.year = year
        self.month = month
        self.day = day

    @classmethod
    def day(cls):
        d = time.localtime()
        self = cls.__new__(cls)     # __new__ 更像是一个静态方法
        self.year = d.tm_year
        self.month = d.tm_mon
        self.day = d.tm_mday
        return self

    def __str__(self):
        return "Date: %d:%d:%d" % (self.year, self.month, self.day)

print(Date(1998, 2, 20))
print(Date.day())
