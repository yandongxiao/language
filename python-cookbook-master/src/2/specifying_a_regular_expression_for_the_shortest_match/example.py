#! /usr/bin/python
# encoding: utf-8
# example.py
#
# Example of a regular expression that finds shortest matches

import re

data = "hello\nworld"
# 点(.)匹配除了换行外的任何字符
# 你可以认为点(.)每次匹配从新的一行开始
# 如果采用最短匹配就无法匹配到任何内容
# 注意贪婪匹配和最短匹配的区别
pattern = re.compile(".*?l")
print pattern.findall(data)     # ['hello', '', 'world', '']
for string in pattern.finditer(data):
    print string.group(),
print

# Sample text
text = 'Computer says "no." Phone says "yes."'

# (a) Regex that finds quoted strings - longest match
str_pat = re.compile(r'\"(.+)\"')       #the default behavior of '*' and '+'
print(str_pat.findall(text))

# (b) Regex that finds quoted strings - shortest match
str_pat = re.compile(r'\"(.+?)\"')  # just add a '?'
print(str_pat.findall(text))
