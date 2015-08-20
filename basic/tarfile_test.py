#! /usr/bin/env python
#---*--- coding:utf8 ---*---


import tarfile

#创建一个tar.gz的文件.
abc = open('abc', 'w')
abc.write("helloworld\n")
abc.write("test echo route \n")
abc.close()

file = tarfile.open('abc.tar.gz', 'w:gz')
file.add('abc')
print file.getmembers()
print file.getnames()

#在创建的.tar.gz文件中增加新的tar.gz文件

add = tarfile.open('net_config.py.tar.gz', 'r')
file.add(add.extractfile('net_config.py').name)
print file.getmembers()
print file.getnames()

file.close()
