#!/usr/bin/env python

import os
import sys
import re

pattern = re.compile(".P")

f = open("ipt.sh")
contents = f.read()
match = pattern.match(contents);
all = pattern.findall(contents)
print all
print match.group()
