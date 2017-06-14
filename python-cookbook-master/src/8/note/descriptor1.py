#!/usr/bin/env python
# encoding: utf-8

class WebFramework(object):
    def __init__(self, name='Flask'):
        self.name = name

    def __get__(self, instance, owner):
        print self, instance, owner
        return self.name

    def __set__(self, instance, value):
        self.name = value


class PythonSite(object):

    webframework = WebFramework()

    version = 0.01

    def __init__(self, site):
        self.site = site


# 类对象和实例对象的区别
# 前者有 webframework，version两个属性，以及 __init__方法，后者仅有一个site属性
# NOTE: 类属性可以使用对象和类访问，多个实例对象共享一个类变量。但是只有类才能修改
# NOTE: 类属性只有通过类对象才能修改
print vars(PythonSite).items()
pysite = PythonSite('ghost')
print vars(pysite)

# 相当于定义了实例的一个新的属性
# 同名属性，实例的属性的优先级更高
pysite.version = 10
print pysite.version
print PythonSite.version


# 调用方法
webframework = WebFramework()
print webframework.__get__(webframework, WebFramework)

# type(pysite).__dict__['webframework'] 返回类型对象的成员变量webframework
# None是__get__的第一个参数
# owner表示webframework对象在哪一个类型对象中定义
print type(pysite).__dict__['webframework'].__get__(None, PythonSite)
