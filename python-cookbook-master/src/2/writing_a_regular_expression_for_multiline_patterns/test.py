#!/usr/bin/env python
# encoding: utf-8

import re

text = '''/* this is a
              multiline comment */
'''

pattern = re.compile(r'/\*(.*?)\*/', flags=re.DOTALL)
print(pattern.findall(text))
