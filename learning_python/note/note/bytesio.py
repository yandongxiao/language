#!/usr/bin/env python
# encoding: utf-8

#from io import StringIO
#from BytesIO import BytesIO
from io import BytesIO

f = BytesIO("中国")
print(f.read())
#print(f.read(5))

f = BytesIO()
f.write("中国")
print(f.getvalue())
