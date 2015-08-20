#! /usr/bin/python

dd1 = {'yan':56, 'zhao':32, 'feng': 44}

dd2 = {'yan':56, 'xxxx':32, 'yyyy': 44}

#dd = dd1 & dd2  # error not supported

dk = dd1.keys() & dd2.keys()

assert len(dk) == 1

dd={}
for key in dd1.keys() & dd2.keys():
    dd[key] = dd1[key]
assert(len(dd) == 1)
assert dd['yan'] == 56

dd={}
dd1.values() & dd2.values() # unsupported operand type(s) for &: 'dict_values' and 'dict_values'


#Note List/tuple support & | -.  and dict().keys() is not list, it is dict_keys.
a = [1,2,3]
b = [1,2]
#c = a - b 
print(c)
