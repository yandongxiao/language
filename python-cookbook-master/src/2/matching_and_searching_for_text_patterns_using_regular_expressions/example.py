#! /usr/bin/python
# example.py
#
# Examples of simple regular expression matching

import re

# Some sample text
text = 'Today is 11/27/2012. PyCon starts 3/13/2013.'

# (a) Find all matching dates
date = '11/27/2012.'
datepat = r'\d+/\d+/\d+'
assert re.match(datepat, text) is None
assert re.match(datepat, date) is not None

pattern = re.compile(datepat)
assert pattern.match(text) is None
assert pattern.match(date) is not None

assert re.findall(datepat, text) is not None
assert pattern.findall(text) is not None

# (b) Find all matching dates with capture groups
# [(11, 27, 2012), (3, 13, 2013)]
datepat = re.compile(r'(\d+)/(\d+)/(\d+)')
for month, day, year in datepat.findall(text):
    print('{}-{}-{}'.format(year, month, day))

# (c) Iterative search
for m in datepat.finditer(text):
    m, d, y = m.groups()
    print('{}-{}-{}'.format(y, m, d))
