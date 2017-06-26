#! /usr/bin/env python3
# encoding: utf-8

class A:
    def __init__(self):
        self.x = 0

class B(A):
    def __init__(self):
        super().__init__()  # 确保父类被正确初始化
        self.y = 1

if __name__ == '__main__':
    b = B()
    # 可以直接访问的原因在于super().__init__()的执行
    # 根本原因在于，实例对象b中存在属性x
    print(b.x, b.y)
