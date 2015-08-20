#!/usr/bin/python

#param 1 : the directory path
#param 2 : the file size

import sys;
import os


"""
if size != 3 :
	print "please give me two param"
	exit -1
"""

dir = sys.argv[1];
size = sys.argv[2];
files = os.listdir(dir)

for file in files:
	filesize = os.path.getsize(file)
	if filesize > int(size) :
		os.remove(file);
	print type(file)
