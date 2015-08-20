#! /usr/bin/python

def func(a,b,c):
    print(a,b,c)

func(1,2,3)

func.b = 20
func.c = 40

#func(100)   # error


def func2(*aa, **bb):
    print(*(aa+(1,)))   # 解开元组.
    print(aa)
    print(bb)

func2(10, 20, bb=99)

def func2(a,b,c,d,e):
    print(a,b,c,d,e)

def partial(func, *targs, **dtargs):
    def newfunc(*narg, **dnargs):
        xtargs = targs + narg
        dnargs.update(dtargs);
        return func(*xtargs, **dnargs)
    return newfunc

newfunc = partial(func2, 10,20, e=40)   #10 is a, 20 is b
newfunc(30, 40) #30 is c, 40 is d
