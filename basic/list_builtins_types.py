#! /usr/bin/python

import builtins # import the modules.
l = [ x for x in dir(builtins) if str(getattr(builtins, x).__class__).find( "\'type\'" )  !=  -1 
                            and str(getattr(builtins, x).__module__ ) == 'builtins' ]

for x in l:
    print("%s" % x)
