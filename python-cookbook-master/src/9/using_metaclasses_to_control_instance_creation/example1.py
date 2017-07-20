#! /usr/bin/env python3
# encoding: utf-8

# example1.py
#
# Not allowing direct instantiation

class NoInstances(type):
    # 这里的__call__不是应用在实例对象上的，而是类对象上的
    # 所以，不允许类对象创建实例
    def __call__(self, *args, **kwargs):
        raise TypeError("Can't instantiate directly")

class Spam(metaclass=NoInstances):
    @staticmethod
    def grok(x):
        print('Spam.grok')

if __name__ == '__main__':
    try:
        s = Spam()
    except TypeError as e:
        print(e)

    Spam.grok(42)
