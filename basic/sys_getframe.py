#! /usr/bin/python

#
# sys._getframe() is an useful function.
#
# sys._getframe().f_locals is a dict which includes all name -> object pairs.
# name is string.
#
def AAA():
    print(sys._getframe().f_locals)     # empty.
    def abc():
        print("abc")
    print (sys._getframe().f_locals)
    
    lvar = (sys._getframe().f_locals)
    for key in lvar:
        if callable(lvar[key]):
            lvar[key]()
AAA()
