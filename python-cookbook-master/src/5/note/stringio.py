#!/usr/bin/env python
# encoding: utf-8

from io import StringIO
#from StringIO import StringIO

f = StringIO(u"中国")
print(f.read().encode("utf-8"))
#print(f.read(5))

f = StringIO()
f.write(u"中国")
print(f.getvalue().encode("utf-8"))
