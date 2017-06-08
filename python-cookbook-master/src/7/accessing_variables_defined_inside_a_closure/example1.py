#! /usr/bin/env python3
# encoding: utf-8

# Example of accessing variables inside a closure

# 闭包的内部变量对于外界来讲是完全隐藏的
# 例如下面的闭包func使用了内部变量n
# 为闭包函数func绑定访问函数，使得外部能够访问和修改n
def sample():
    n = 0
    def set_n(num):
        # 1. 如果变量在函数内部被定义或赋值，那么它就是一个局部变量
        # 2. 这是python3的特性, python2只支持global值
        nonlocal n
        n = num

    def get_n():
        return n

    def func():
        print("n=", n)

    func.set_n = set_n
    func.get_n = get_n
    return func

class sample2:
    def __init__(self):
        self.n = 0

    def __repr__(self):
        print(self.n)

    def get_n(self):
        return self.n

    def set_n(self, n):
        self.n = n

    # 对应在sample中就是闭包函数
    def __call__(self):
        print("n=", self.n)

if __name__ == '__main__':
    f = sample()
    f()
    n= 0
    f.set_n(10)
    f()
    print(f.get_n())

    print("-------")
    f = sample2()
    f()
    n= 0
    f.set_n(10)
    f()
    print(f.get_n())

