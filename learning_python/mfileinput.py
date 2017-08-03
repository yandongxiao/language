#!/usr/bin/env python
# encoding: utf-8

import fileinput

# AttributeError: FileInput instance has no attribute '__exit__'
for line in fileinput.input():
    print line,
