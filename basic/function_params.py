#! /usr/bin/python

"""
    no param
"""
def func_1():
    pass

func_1()
try:
    func_1(2)
except Exception as e:
    print (e)



"""
    have fix number params

    try:    #there must have statement, you can give it pass.
        func_2(arg1=1, 2)   # the SyntaxError can not be catched.
    except Exception as e:
        print (e)
"""
def func_2(arg1, arg2):
    pass

func_2(1, 2)
func_2(arg1=1, arg2=2)
func_2(arg2=2, arg1=1 )
func_2(1, arg2=2)
try:
    func_2(10)
except Exception as e:
    print (e)


"""
    have default number
"""
def func_3(arg1 = 1, arg2 = 2):
    pass

func_3()
func_3(1)
func_3(1,2)
try:
    func_3(1,2,3)
except Exception as e:
    print (e)


"""
    have 2 or more params
"""
def func_4(arg1, arg2, *args):
    pass

func_4(1,2)
func_4(1,2,3)
func_4(1,2,4,5)


"""
    only require key=value format
"""
def func_5(*, arg1, arg2):
    pass

try:
    func_5 (1,2)
except Exception as e:
    print (e)

try:
    func_5 ()
except Exception as e:
    print (e)
func_5(arg1=1, arg2=2)


"""
    must have two params
    other format must be key=value
"""
def func_6(arg1, arg2, **kvs):
    pass
try:
    func_6 (1, 2, 3)
except Exception as e:
    print (e)
func_6(1,2,a=3)

"""
    must have at leat two params
    other format must be key=value
"""
def func_7(arg1, arg2, *_, **kvs):  # the _ must have.
    pass
func_7(1,2,3,4,5,a=7,b=8)

"""
    must have at leat two params
    other format must be key=value
"""
def func_8(arg1, arg2, *args, **kvs):
    pass
