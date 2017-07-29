#! /usr/bin/env python3
# encoding: utf-8

# 这是一个元类
class NoInstances(type):
    # 这里的__call__不是应用在实例对象上的，而是类对象上的
    # 所以，不允许类对象创建实例
    # 类对象指定调用()，是实例化对象的过程，也会调用元类的__call__方法
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
