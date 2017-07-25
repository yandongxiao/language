#!/usr/bin/env python
# encoding: utf-8

import itertools

assert list(itertools.dropwhile(lambda x: x<5, [4, 5, 6, 3, 8])) == [5, 6, 3, 8]
