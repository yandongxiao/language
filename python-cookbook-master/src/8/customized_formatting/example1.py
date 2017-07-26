#! /usr/bin/env python
# encoding: utf-8

# format方式自定义格式化字符串
# 支持普通模式，位置模式，关键字模式，实例属性模式
# 总之，支持变量插入模式

# 普通模式
'{} is {}'.format(1,2) == '1 is 2'

# 支持位置
'{1} is {0}'.format(1,2) == '2 is 1'

# 支持关键字
'{name} is {age}'.format(name='jack', age=10) == 'jack is 10'

# 支持类属性
class Person(object):
    def __init__(self, name, age):
        self.name = name
        self.age = age
'{p.name} is {p.age}'.format(p=Person('jack', 10)) == 'jack is 10'


_formats = {
    'ymd' : '{d.year}-{d.month}-{d.day}',
    'mdy' : '{d.month}/{d.day}/{d.year}',
    'dmy' : '{d.day}/{d.month}/{d.year}'
    }

class Date:
    def __init__(self, year, month, day):
        self.year = year
        self.month = month
        self.day = day

    def __format__(self, code=''):
        print "dsadsall", code
        if code == '':
            code = 'ymd'
        fmt = _formats[code]
        return fmt.format(d=self)

d = Date(11, 11, 11)
#print format(date)
#print '{d.year}-{d.month}-{d.day}'.format(d=d)
print '{}'.format(d)
