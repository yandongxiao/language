#! /usr/bin/env python3
#encoding: utf-8

# Example involving new and some of its problems

import weakref


class Spam:
    _spam_cache = weakref.WeakValueDictionary()     # 维护一个类变量
    # NOTE：可以自定义__new__的参数
    def __new__(cls, name):
        if name in cls._spam_cache:
            return cls._spam_cache[name]
        else:
            self = super().__new__(cls)         # 调用父类的方法
            cls._spam_cache[name] = self
            return self

    def __init__(self, name):
        print('Initializing Spam')
        self.name = name


if __name__ == '__main__':
    s = Spam('Dave')
    t = Spam('Dave')
    print(s is t)
