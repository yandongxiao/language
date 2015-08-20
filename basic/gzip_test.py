#!/usr/bin/env python
#--*- coding:utf8 --*--


import gzip

gz = gzip.GzipFile('gzip_test.py.bak.gz', 'a')
gz.write('another line\n')
gz.close()

gz = gzip.open('gzip_test.py.bak.gz')
print gz.read()
gz.close()
