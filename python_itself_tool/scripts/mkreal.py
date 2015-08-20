#! /usr/bin/env python3
# -*- coding:utf8 -*-
# mkreal
#
# turn a symlink to a directory into a real directory

import sys
import os
from stat import *

join = os.path.join

error = 'mkreal error'

BUFSIZE = 32*1024

def mkrealfile(name):
    st = os.stat(name) 			#Get the mode，这也是链接文件的mode
    mode = S_IMODE(st[ST_MODE])	
    linkto = os.readlink(name) # Make sure again it's a symlink,linkto是一个字符串，相对路径。至少做实验的时候是这样的.
    f_in = open(name, 'r') # This ensures it's a file
    os.unlink(name)				#这里的代码很关键
    f_out = open(name, 'w')
    while 1:
        buf = f_in.read(BUFSIZE)
        if not buf: break
        f_out.write(buf)
    del f_out 				# Flush data to disk before changing mode
    os.chmod(name, mode)

def mkrealdir(name):
    st = os.stat(name) 				# Get the mode
    mode = S_IMODE(st[ST_MODE])
    linkto = os.readlink(name)
    files = os.listdir(name)
    os.unlink(name)			#断开了软链接.
    os.mkdir(name, mode)
    os.chmod(name, mode) 	#是不是有点重复啊?
    print('linkto : ', linkto)
    linkto = join(os.pardir, linkto)	#竟然是..
    print ("xxx : ", os.pardir)
    print('linkto : ', linkto)
    #
    for filename in files:
        if filename not in (os.curdir, os.pardir):
            os.symlink(join(linkto, filename), join(name, filename))

def main():
    sys.stdout = sys.stderr
    progname = os.path.basename(sys.argv[0]) 	#跟basename命令的效果一样
    if progname == '-c': progname = 'mkreal'
    args = sys.argv[1:]
    print (args, sys.argv)
    if not args:
        print('usage:', progname, 'path ...')
        sys.exit(2)
    status = 0
    for name in args:
        if not os.path.islink(name):
            print(progname+':', name+':', 'not a symlink')
            status = 1
        else:
            if os.path.isdir(name):
                mkrealdir(name)
            else:
                mkrealfile(name)
    sys.exit(status)

if __name__ == '__main__':
    main()
