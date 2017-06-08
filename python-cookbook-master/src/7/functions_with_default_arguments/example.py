#! /usr/bin/env python3
#encoding: utf-8

# Examples of a function with default arguments

# (a) Dangers of using a mutable default argument
# NOTE: 如果默认形参是可变对象，那么默认值如果被改变
# 下次再次调用该函数时，可变对象的内容就是上次修改过的内容
# NOTE: 默认参数的值仅仅在函数定义的时候赋值一次，即值不但可以是常量也可以是变量
# 但是如果变量的值在后面被改变过，不会影响默认参数的值
# NOTE:默认参数的值应该是不可变的对象
def spam(b=[]):
    return b

a = spam()
print(a)
a.append(1)
a.append(2)
b = spam()
print(b)       #  Carefully observe result
print('-'*10)

# 以下是替代方案
# (b) Better alternative for mutable defaults
def spam(b=None):
    # 注意与if not b:的区别：not b不准确，
    # 即便是提供了0，""等参数，函数仍然认为我们没有提供参数
    if b is None:
        b = []
    return b

a = spam()
print(a)
a.append(1)
a.append(2)
b = spam()
print(b)
print('-'*10)

# (c) Example of testing if an argument was supplied or not
# NOTE：注意与None的区别
# object(): 创建一个独一无二的私有对象实例
_no_value = object()
def spam(b=_no_value):
    if b is _no_value:
        print("No b value supplied")
    else:
        print("b=", b)

spam()
spam(None)
spam(0)
spam([])
