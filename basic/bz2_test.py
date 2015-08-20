#!/usr/bin/env python
#--*--coding:utf8--*--

from bz2 import *

#产生一个.bz2的数据包
compressor = BZ2Compressor()
compressor.compress('test test test\n')
compressor.compress('done done done.')
file = open('test.bz2', 'w')
file.write(compressor.flush())
file.close()

#读取.bz2文件
de = BZ2Decompressor()
file = open('test.bz2', 'r')
print de.decompress(file.read())

#作为一个文件对象，读取.bz2压缩文件.
file = BZ2File('test.bz2', 'r')
i=1
for line in file.readlines():
        print i, line,
        i += 1
