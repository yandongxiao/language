#! /usr/bin/env python
# encoding: utf-8

# format方式自定义格式化字符串
# 支持普通模式，位置模式，关键字模式，实例属性模式
# 总之，支持变量插入模式

# 普通模式
assert '{} is {}'.format(1,2) == '1 is 2'

# 支持位置
assert '{1} is {0}'.format(1,2) == '2 is 1'

# 支持关键字
assert '{name} is {age}'.format(name='jack', age=10) == 'jack is 10'

# 支持类属性
class Person(object):
    def __init__(self, name, age):
        self.name = name
        self.age = age
assert '{p.name} is {p.age}'.format(p=Person('jack', 10)) == 'jack is 10'


# __format__ 方法是为了让实例支持一下格式调用
# '{}'.format(p)
class Person(object):
    def __init__(self, name, age):
        self.name = name
        self.age = age

    # NOTE: __format__方法需要两个参数
    def __format__(self, code):
        return "{self.name} is {self.age}".format(self=self)

assert 'hello, {0}, {1}'.format(Person("jack", 10), 1) == 'hello, jack is 10, 1'


# case

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
        if code == '':
            code = 'ymd'
        fmt = _formats[code]
        return fmt.format(d=self)

d = Date(11, 11, 11)
assert format(d) == '11-11-11'
# 这个不会调用__deploy__方法的
assert '{d.year}-{d.month}-{d.day}'.format(d=d) == '11-11-11'
