#!/usr/bin/env python
#-*- coding:utf8 -*-

#删除某目录下所有的文件大小大于K字节的普通文件
#os.argv[1] 指定目录
#os.argv[2] 指定大小

import os,sys
from stat import *

def usage():
	print './rm_size /xx/xx/xx kkk'

def perror(msg):
	sys.stderr.write(msg);
	sys.exit(-1)

#检查参数
def int_check(param):
	try:
		num = int(sys.argv[2])
	except ValueError:
		perror('not a legal num\n')

def path_check(param):
	if (False == os.path.isdir(param)):
		perror("the path do not exist\n")

def check_params():
	if 3 != len(sys.argv):
		perror('params size not right\n')
	path_check(sys.argv[1])
	int_check(sys.argv[2])

def filetype_check(file):
	try:
		st = os.stat(file)
		if S_ISREG(st[ST_MODE]): 
			return True
	except:
		return False
	return False

if __name__ == '__main__':
	check_params()			#不符合要求的参数导致程序直接推出
	dirpath = sys.argv[1]
	size = int(sys.argv[2])
	filenames = os.listdir(dirpath)
	for temp in filenames :
		filepath = os.path.join(dirpath, temp);
		if not filetype_check(filepath):
			continue;
		filesize = os.path.getsize(filepath)
		print filesize, size
		if filesize > size:
			# os.remove(); 	这个函数太危险，也不说一声
			os.system('rm -i ' + filepath)  
