#!/usr/bin/env python
# encoding: utf-8

persons = [
    {"first name": "alice", "second name": "roony"},
    {"first name": "alice", "second name": "jose"},
]


for item in sorted(persons, key=lambda p: p["second name"]):
    print item

# attrgetter中包含的字符串需要是对象的一个属性
# attrgetter可以按照多个属性进行排序
# 所以attrgetter对于类实例来说很好用
#from operator import attrgetter
#for item in sorted(persons, key=attrgetter("second name")):
#    print item
