#! /usr/bin/python
# example.py
#
# Examples of simple regular expression substitution

import re

# Some sample text
text = 'Today is 11/27/2012. PyCon starts 3/13/2013.'

datepat = re.compile(r'(\d+)/(\d+)/(\d+)')

# (a) Simple substitution
print(datepat.sub(r'\3-\1-\2', text))

# (b) Replacement function
from calendar import month_abbr

def change_date(m):
    #mon_name = month_abbr[int(m.group(1))]
    #return '{} {} {}'.format(m.group(2), mon_name, m.group(3))
    print "====", m.group()
    return '{} {} {}'.format(*(m.groups()))

print(datepat.sub(change_date, text))   # when you can pass a value and when you can pass a func.
