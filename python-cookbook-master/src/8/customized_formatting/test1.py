#!/usr/bin/env python
# encoding: utf-8

class Date:
    def __init__(self, year, month, day):
        self.year = year
        self.month = month
        self.day = day

    def __format__(self, fmt):
        print "nihao"
        return fmt.format(y=self.year, m=self.month, d=self.day)

d = Date("1998", "7", "20")
#print r'{d}-{m}-{y}'.format(d=d.day, m=d.month, y=d.year)
#print format(d, r'{d}-{m}-{y}')
print r'{d}-{m}-{y}'.format(d)  # 如何支持这种形式
