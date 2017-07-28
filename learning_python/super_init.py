#!/usr/bin/env python
# encoding: utf-8

# 如果你尝试将super给注释掉以后，初始化工作就会被中断

class sample1(object):
    def __init__(self):
        print("sample1")
        return super(sample1, self).__init__()


class sample2(object):
    def __init__(self):
        print("sample2")
        return super(sample2, self).__init__()


class me(object):
    def __init__(self):
        print("callme")
        return super(me, self).__init__()


class person(sample1, sample2, me):
    def __init__(self):
        return super(person, self).__init__()


p = person()
