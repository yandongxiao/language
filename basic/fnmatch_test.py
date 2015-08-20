#! /usr/bin/env python
# -*- coding:utf8 -*-

import os
import fnmatch

def findall(topdir, pattern):
	for dirpath, dirnames, files in os.walk(topdir):           #这里的os.walk的三个返回值与其它版本的不一样.
		for name in files:
			print name
			if fnmatch.fnmatch(name, pattern):
				yield os.path.join(dirpath, name)

for pyfile in findall('.', '*.py'):
	print pyfile


