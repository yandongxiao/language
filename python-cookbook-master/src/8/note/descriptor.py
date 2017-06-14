#!/usr/bin/env python
# encoding: utf-8

# see http://www.jianshu.com/p/250f0d305c35 for more

# 定义了一个类WebFramework，它实现了描述符协议__get__和__set__
class WebFramework(object):
    def __init__(self, name='Flask'):
        self.name = name

    def __get__(self, instance, owner):
        return self.name

    def __set__(self, instance, value):
        print "setter"
        self.name = value


class PythonSite(object):
    version = 0.01
    def __init__(self, site):
        self.site = site
        self.webframework = WebFramework()

# NOTE: 实例的__dict__中的对象不可能是一个描述器
ps = PythonSite("baidu")
print(ps.webframework)  # 只是返回了实例对象本身
