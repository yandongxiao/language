#!/usr/bin/env python
# -*- coding:utf8 -*-


import os,sys
import re
from stat import *
filename='.'

def main(filename):
    dirs = os.listdir(filename)
    for f in dirs:
    f = os.path.join(filename,f);
        st = os.stat(f)
        if(S_ISDIR(st[ST_MODE])):
            main(f)
        if not S_ISREG(st[ST_MODE]):
            continue;
        file=open(f,'r')
        for words in file.readlines():
            if re.search(sys.argv[1], words):
                print file.name, " : ", words,
    file.close()        

if __name__ == '__main__':
    if(len(sys.argv) == 3):
    filename=sys.argv[2]    
    main(filename)
