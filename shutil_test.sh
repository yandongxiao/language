#! /usr/bin/env python
#---*--- coding:utf8 ---*---

import shutil

#复制文件abc，拷贝文件为abc.bak

abc = open('abc', 'w')
abc.write("helloworld\n")
abc.write("test echo route \n")
abc.close()
#shutil.copy('abc', 'abc.bak') 		#直接给出两个文件的名称即可
#shutil.copyfile('abc', 'abc.bak')   #两者之间的区别

shutil.copymode('abc', 'abc.bak')
