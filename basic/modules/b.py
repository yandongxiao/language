#! /usr/bin/python

from a import a
print(a)    #10
a = -1
print(a)    #-1
from a import a
print(a)    #-1


import a  
print(a.a)  # 10
a.a = -1
print(a.a)  # -1

import a
print(a.a)  #-1
