#! /usr/bin/python
# example.py
#
# Find out what two dictionaries have in common

a = {
   'x' : 1,
   'y' : 2,
   'z' : 3
}

b = {
   'w' : 10,
   'x' : 11,
   'y' : 2
}

print('Common keys:', a.viewkeys() & b.viewkeys())
print('Keys in a not in b:', a.viewkeys() - b.viewkeys())
#print('(key,value) pairs in common:', a.items() & b.items())

for key in a.viewkeys() & b.viewkeys():
    if a[key] == b[key]:
        print (key, a[key])
