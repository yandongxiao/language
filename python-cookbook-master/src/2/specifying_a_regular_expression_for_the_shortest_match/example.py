#! /usr/bin/python
# example.py
#
# Example of a regular expression that finds shortest matches

import re

# Sample text
text = 'Computer says "no." Phone says "yes."'

# (a) Regex that finds quoted strings - longest match
str_pat = re.compile(r'\"(.+)\"')       #the default behavior of '*' and '+'
print(str_pat.findall(text))

# (b) Regex that finds quoted strings - shortest match
str_pat = re.compile(r'\"(.+?)\"')  # just add a '?'
print(str_pat.findall(text))



