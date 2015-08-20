#! /usr/bin/python

from fnmatch import fnmatchcase as match
import re

addresses = [
    '5412 N CLARK ST',
    '1060 W ADDISON ST',
    '1039 W GRANVILLE AVE',
    '2122 N CLARK ST',
    '4802 N BROADWAY',
]

a = [addr for addr in addresses if match(addr, '* ST')]
print (a)

a = [addr for addr in addresses if re.match(r'.*ST', addr)]
print (a)

b = [addr for addr in addresses if match(addr, '54[0-9][0-9]*CLARK*')]
print(b)

b = [addr for addr in addresses if re.match(r'54[0-9][0-9].*CLARK.*', addr) ]
print(b)
