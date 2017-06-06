#! /usr/bin/env python
# encoding: utf-8

import re

# Some sample text
text = 'Today is 11/27/2012. PyCon starts 3/13/2013.'


pattern = re.compile(r'\d+/\d+/\d+')
print pattern.findall(text) # 返回一个list

pattern = re.compile(r'(\d+)/(\d+)/(\d+)')
for m, d, y in pattern.findall(text):
    print m, d, y

# finditer返回的是Match对象的iter
# 匹配结果需要调用Match对象的group()、groups或group(index)方法
print "==============="
pattern = re.compile(r'(\d+)/(\d+)/(\d+)')
for p in pattern.finditer(text):
    print p.group()
    print p.group(0)    # 与p.group()一样
    print p.group(1)
    print p.group(2)
    print p.group(3)
    print p.groups()
