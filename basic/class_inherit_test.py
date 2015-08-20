#! /usr/bin/python

"""
In python, inherit is very special. 
    The format is class B(A).
    You can invoke super(B, self) or super(B, b) to get the Class A instance.

Note:
    what is private ? __private is, but public and __init__ is not.
    python modify __private to _A__private. And _A__private is inherited too!!!

    when public method do not be implemented in B, b.public() will invoke public in A.

    you can call private method like: b._A__private()
"""

class A(object):
    """
        a will not be inherited, if __init__ is not called.
        two ways to call it :
        1. super(B, self).__init__()
        2. in B, there is no __init__ method.
    """
    def __init__(self):
        self.a = 10     
        print ('hello')

    """
        It will not be inherited by B. you can invoke it like: a._A_private
    """
    def __private(self):
        print ('A.__private()')

    """
        It will be inherited by B. That is, if B do not overwrite it, b.public() will call it.
        If B do overwrite it, and you want call it first, you can do like this : super(B, self).public()
    """
    def public(self):
        print ('A.public()')

class B(A):
    def __init__(self):
        super(B, self).__init__()
        print ('world')

    def __private(self):
        super(B, self)._A__private()    # super(B, self).__private() or super(B, self).private() will happend error
        print ('B.__private()')

    def public(self):
        super(B, self).public()
        print ('B.public()')

b = B()
b.public()
b._B__private()
print(b.a)
