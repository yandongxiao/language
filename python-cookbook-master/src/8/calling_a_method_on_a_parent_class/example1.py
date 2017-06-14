#! /usr/bin/env python3

class A:
    def spam(self):
        print('A.spam')

class B(A):
    def spam(self):
        print('B.spam')
        # super().spam()      # Call parent spam()
        # super() 等价于 super(__class__, <first argument>)
        super(B, self).spam()   # 坏处是B如果被赋值为其它变量，那么super(B, self)将会出错

if __name__ == '__main__':
    b = B()
    b.spam()
