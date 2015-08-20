#!/usr/bin/env python
# -*- codin:utf8 -*-

a=10
try:
    print (a)
except Exception as e:
    print (e.args)
finally:
    print ('finally')

if __debug__:   # why __debug__ is not zero?
	print ('hellp')
