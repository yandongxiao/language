#!/usr/bin/env python
# encoding: utf-8


persons = [
    {"name":"jack", "age":10},
    {"name":"bob", "age":20},
    {"name":"alice", "age":30}
]

# lambda限制
# NOTE: 你只能指定单个表达式
# NOTE: 表达式的返回值就是匿名函数的返回值
# NOTE: 不能包含其他的语言特性了， 包括多个语句、条件表达式、迭代以及异常处理等等。
persons.sort(key=lambda p: p["age"])
print persons


# 匿名函数捕获变量值
# NOTE: 捕获变量只是意味着，lambda函数捕获到了x的引用，被引用次数+1.
# 确保lambda函数永远能获取到x的值
x = 10
a = lambda y: x + y     # 使用外部变量x
x = 20
b = lambda y: x + y     # 使用外部变量x
assert a(10) == 30
assert b(10) == 30

def myf():
    x=100
    # lambda函数使用了全局变量x, 因为lambda关键字简历的引用关系就是全局变量x；
    # lambda函数被调用时，动态获取全局变量x的值；
    # 这里的局部变量没有起到任何作用；
    assert a(10) == 30
myf()


# 如果想一直使用定义lambda函数时x的值，将x的值得变为一个lambda函数的参数
# 这是利用了：函数的默认形参在函数定义时确定
x = 10
a = lambda y, x=x: x + y     # 使用外部变量x
x = 20
b = lambda y: x + y     # 使用外部变量x
assert a(10) == 20
assert b(10) == 30

# 元组推导，并返回匿名函数
for f in (lambda x, n=n: x+n for n in xrange(0, 5)):
    print f(0)
