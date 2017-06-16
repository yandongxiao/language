#!/usr/bin/env python
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
        return cls(d.tm_year, d.tm_mon, d.tm_mday)

    def __str__(self):
        return "Date: %d:%d:%d" % (self.year, self.month, self.day)

print Date(1998, 2, 20)
print Date.day()
