#!/usr/bin/env python3
# encoding: utf-8

# 给类添加 __slots__ 属性来极大的减少实例所占的内存
# normal: 在64位的Python上面要占用428字节
# __slots__: 内存占用下降到156字节
# 你应该只在那些 经常 被使用到的  用作数据结构  的类上定义slots
class Date:
    # 以列表表示
    # 这是python3的一个特性
    __slots__ = ['year', 'month', 'day']
    def __init__(self, year, month, day):
        self.year = year
        self.month = month
        self.day = day
        # 使用了__slots__属性以后，不能再给实例添加新的属性了
        # self.sock = "nihao"


date = Date(1988, 6, 21)
print(date.year)
