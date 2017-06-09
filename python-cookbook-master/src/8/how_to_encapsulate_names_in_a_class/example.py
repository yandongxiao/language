#! /usr/bin/env python3
# encoding: utf-8

# 1. Python程序员不去依赖语言特性去封装数据
# 2. 命名规约
#    NOTE: 任何以单下划线_开头的名字都应该是内部实现
#    NOTE: 使用下划线开头的约定同样适用于模块名和模块级别函数
#    _sock.py 不是一个你想导入的模块
#    NOTE: 使用双下划线开始会导致访问名称变成其他形式.
#          私有属性会被分别重命名为 _B__private 和 _B__private_method。
#          这时候你可能会问这样重命名的目的是什么，答案就是继承——这种属性通过继承是无法被覆盖的。
#    NOTE: 你应该让你的非公共名称以单下划线开头。但是，如果你清楚你的代码会涉及到子类，
#          并且有些内部属性应该在子类中隐藏起来，那么才考虑使用双下划线方案。
#    NOTE: 有时候你定义的一个变量和某个保留关键字冲突，这时候可以使用单下划线作为后缀, 如lambda_ = 1

class B:
    def __init__(self):
        self.__private = 0

    def __private_method(self):
        print('B.__private_method', self.__private)

    def public_method(self):    # 调用自己的函数
        self.__private_method()

class C(B):
    def __init__(self):         # _C__init__
        super().__init__()      # _B__init__
        self.__private = 1      # Does not override B.__private
    def __private_method(self): # Does not override B.__private_method()
        print('C.__private_method')

c = C()
c.public_method()
c._C__private_method()
