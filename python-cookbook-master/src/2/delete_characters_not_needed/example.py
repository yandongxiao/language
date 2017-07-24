#!/usr/bin/env python
# encoding: utf-8

s = ' hello world \n'
print s.strip()

t = '-----hello====='
assert t.lstrip('-') == 'hello====='
assert t.rstrip('=') == '-----hello'


import re
s = ' hello     world\n'
print re.sub(r'\s+', ' ', s)
