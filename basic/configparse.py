#! /usr/bin/env python
# ---*--- coding:utf-8 --*---

import os, sys, re
from ConfigParser import *

if __name__ == '__main__':
        if len(sys.argv) !=2:
                print ("I want two parameters, but you give me %d.", len(sys.argv))
                exit(-1)
        filename = sys.argv[1]
        if not os.path.isfile(filename):
                print ("please give me the right file")
                exit(-1)
        parser = ConfigParser()
        parser.read(filename)
        for section in parser.sections():
                for option in parser.options(section):
                        print option, "=", parser.get(section, option)
