#!/usr/bin/env python3
# encoding: utf-8

import gzip

f = open('testfile.gz', 'wb')   # 注意这里是二进制形式
with gzip.open(f, 'wt') as g:   # gzip可以作用在类文件对象上面
    g.write("中国")
f.close()

with gzip.open("testfile.gz", 'rt') as g:
    print(g.read())
