#! /usr/bin/env python
# -*- coding:utf8 -*-

import sys
import re
import os

def main():
    filename = sys.argv[1]
    #打开文件
    fr = open(filename, 'r')    
    fw = open(filename+'.bak', 'wx')
    #读取文件的每一行
    for line in fr.readlines():
        line=re.sub('\t', '        ', line)
        fw.write(line)
    
    os.remove(filename)
    os.rename(filename+'.bak', filename)
    os.chmod(filename, 0700)
if __name__ == '__main__':    
    main()
