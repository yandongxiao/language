#! /usr/bin/env python3
#encoding: utf-8

# 通过类方法定义新的构造方法

import time

class Date:
    # Primary constructor
    def __init__(self, year, month, day):
        self.year = year
        self.month = month
        self.day = day

    # Alternate constructor
    @classmethod
    def today(cls):
        t = time.localtime()
        return cls(t.tm_year, t.tm_mon, t.tm_mday)      # 本质上还是调用了__init__方法

if __name__ == '__main__':
    a = Date(2012, 12, 21)
    b = Date.today()
    print(a.year, a.month, a.day)
    print(b.year, b.month, b.day)

    # 需要了解classmethod和staticmethod是如何继承的
    class NewDate(Date):
        pass

    c = Date.today()
    d = NewDate.today()
    print('Should be Date instance:', c)
    print('Should be NewDate instance:', d)
