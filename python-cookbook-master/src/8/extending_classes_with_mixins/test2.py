#!/usr/bin/env python3
# encoding: utf-8

def sample1(cls):
    cls_getitem = cls.__getitem__
    cls_setitem = cls.__setitem__
    cls_delitem = cls.__delitem__

    def __getitem__(self, key):
        print('Getting %s' % key)
        return cls_getitem(self, key)

    def __setitem__(self, key, val):
        print('Setting %s = %r' % (key, val))
        if not isinstance(val, str):
            raise TypeError("except a string val")
        cls_setitem(self, key, val)

    def __delitem__(self, key):
        print('Deleting %s' % key)
        return cls_delitem(self, key)

    cls.__getitem__ = __getitem__
    cls.__setitem__ = __setitem__
    cls.__delitem__ = __delitem__
    return cls

@sample1
class LoggedDict(dict):
    pass

d = LoggedDict()
d['x'] = "23"
print(d['x'])
try:
    d['x'] = 100
except TypeError as e:
    print(e)
print(d['x'])
