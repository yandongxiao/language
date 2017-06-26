#!/usr/bin/env python
# encoding: utf-8

# NOTE: 无论是装饰器还是函数本身带参数，都会新增一个函数嵌套
# 带参数的装饰器本质上利用了装饰器是函数，函数是对象，对象可调用

print("===== decorator_func ====")
def decorator(func):
    print "hello"
    return func
@decorator
def foo():
    pass

foo()


print("===== decorator_func_args ====")
def decorator_func_args(func):
    def handle_args(*args, **kwargs): #处理传入函数的参数
        print "begin"
        func(*args, **kwargs)   #函数调用
        print "end"
    return handle_args

@decorator_func_args
def foo2(a, b=2):
    print a, b

foo2(1)


print("===== decorator_with_params ====")
def decorator_with_params(arg_of_decorator):#这里是装饰器的参数
    print arg_of_decorator
    #最终被返回的函数
    def newDecorator(func):
        return func
    return newDecorator

# 等价于
# dec = decorator_with_params("deco_args")
# foo3 = dec(foo3)
@decorator_with_params("deco_args")
def foo3():
    print("foo3")
foo3()


# 无论是装饰器还是函数本身带参数，都会新增一个函数嵌套
print("===== decorator_whith_params_and_func_args ====")
def decorator_whith_params_and_func_args(arg_of_decorator):
    def handle_func(func):
        def handle_args(*args, **kwargs):
            print "begin"
            func(*args, **kwargs)
            print "end"
            print arg_of_decorator, func, args,kwargs
        return handle_args
    return handle_func

# 等价于
# dec = decorator_whith_params_and_func_args("123")
# foo4 = dec(foo4)
@decorator_whith_params_and_func_args("123")
def foo4(a, b=2):
    print "Content"

foo4(1, b=3)
