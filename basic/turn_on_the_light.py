#! /usr/bin/python

from sys import argv    # for arguments.
from re import match    # for match.

print ("argv len is %d" % len(argv) )
i = 0   # variable can not be right value when the first time.
for x in argv :
    print("  argv[%d] = %s" % (i, argv[i]) )
    i += 1  # no i++ in python.

turnOn = False      #the key value has different color.

#another compare is argv[1]="on"
if len(argv) > 1 : 
    if match("[Oo][Nn]", argv[1]) :   #Try to apply the pattern at the start of the string 
        turnOn = True

if turnOn :
    print("light is on")
else :
    print("light is down")
