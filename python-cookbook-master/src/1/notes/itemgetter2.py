#!/usr/bin/env python
# encoding: utf-8

persons = [
    {"first name": "alice", "second": "roony"},
    {"first name": "alice", "second": "jose"},
]


for item in sorted(persons, key=lambda p: p["second"]):
    print item

# attrgetter中包含的字符串需要是对象的一个属性
# attrgetter可以按照多个属性进行排序
# 所以attrgetter对于类实例来说很好用
# NOTE: 此处应该使用itemgetter
from operator import attrgetter
from operator import itemgetter
for item in sorted(persons, key=itemgetter("first name", "second")):
    print item
