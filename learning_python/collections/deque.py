#!/usr/bin/env python
# encoding: utf-8

'the name is pronounced “deck” and is short for “double-ended queue'
from collections import deque


a = "helloworld"

a = deque(a, maxlen=3)
print list(a)
