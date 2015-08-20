#! /usr/bin/python

"""
    get the file size
"""

import os
import sys

sys.argv = sys.argv[1:]

for name in sys.argv:
    size = os.path.getsize(name);
    print ("%s : %d" % (name,size) )
