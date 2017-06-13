#!/usr/bin/env python
# encoding: utf-8

# NOTE: 不要使用可变变量作为函数参数的默认值
def get(v = []):
    v.append(1)
    return v
assert get() == [1]
assert get() == [1, 1]

# NOTE: 允许传递给默认参数一个变量
# NOTE：定义函数是变量的值是多少，默认参数的值就是多少。后面变量的值的改变，不会影响默认参数
# NOTE：第二条的成立，当然建立在变量是不可修改变量了
arg = 1
def get(v=arg):
    return v
arg=2
assert get() == 1


# NOTE: 如果希望两个closure相互独立，就不要共享v
def add():
    def func(a):
        return v + a
    return func

l = []
for v in [1, 2, 3]:
    l.append(add())
for i in l:
    assert i(10) == 13

# 如果None也做为了一个用户的输入的情况
_obj = object()
def get(arg=_obj):
    if arg is _obj:
        print "no argument"
    else:
        print arg

get()
get(None)
get(0)
