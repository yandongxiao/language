#! /usr/bin/env python3
# Tricky initialization problem involving multiple inheritance.
# Does NOT use super()

class Base:
    def __init__(self):
        print('Base.__init__')

class A(Base):
    def __init__(self):
        Base.__init__(self)
        print('A.__init__')

class B(Base):
    def __init__(self):
        Base.__init__(self)
        print('B.__init__')

class C(A, B):
    def __init__(self):
        A.__init__(self)
        B.__init__(self)
        print('C.__init__')

if __name__ == '__main__':
    # Please observe double call of Base.__init__
    c = C()

# 确保Base在C中只执行一次，需要类A和B的配合
# 即A，B，C都使用super方式初始化基类
class Base:
    def __init__(self):
        print('Base.__init__')

class A(Base):
    def __init__(self):
        super().__init__()
        print('A.__init__')

class B(Base):
    def __init__(self):
        super().__init__()
        print('B.__init__')

class C(B, A):      # 顺序是从右到左
    def __init__(self):
        # 虽然是多重继承, 但是只需要执行super().__initj()即可
        # NOTE: 如果A和B的__init__方法有参数，且不相同时怎么办？
        super().__init__()     # Only one call to super() here
        print('C.__init__')

if __name__ == '__main__':
    # Observe that each class initialized only once
    c = C()
