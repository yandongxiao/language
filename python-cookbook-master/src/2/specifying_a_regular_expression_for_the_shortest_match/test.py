#!/usr/bin/env python
# encoding: utf-8

import re

text = 'Computer says "no." Phone says "yes."'

# 默认是贪婪匹配
patter = re.compile(r'\"(.+)\"')
print patter.findall(text)

# 采用最短匹配
patter = re.compile(r'\"(.+?)\"')
print patter.findall(text)
