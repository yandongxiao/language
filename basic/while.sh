#! /usr/bin/python

import re

x = "abcdexyzdsa"
found = False

while x :
    if re.match("xyz", x):
        print("found")
        break;
    else:
        x = x[1:]
else:
    print("not found")
    found = False;

