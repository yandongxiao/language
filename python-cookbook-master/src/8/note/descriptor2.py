#!/usr/bin/env python
# encoding: utf-8

class WebFramework(object):
    def __init__(self, name='Flask'):
        self.name = name

    def __get__(self, instance, owner):
        #print self, instance, owner
        return self.name

    def __set__(self, instance, value):
        self.name = value


class PythonSite(object):
    webframework = WebFramework()

    version = 0.01

    def __init__(self, site):
        self.site = site

    def get_site(self):
        return self.site

    @classmethod
    def get_version(cls):
        return cls.version

    @staticmethod
    def find_version():
        return PythonSite.version

# A.f 是 unbound method, 而 a.f 是 bound method
ps = PythonSite('ghost')
print ps.get_version
print type(ps).__dict__['get_version'].__get__(ps, type(ps))
# 我们发现__get__操作返回的是一个可调用对象
assert ps.get_version == type(ps).__dict__['get_version'].__get__(ps, type(ps))
assert PythonSite.__dict__['get_version'].__get__(None, PythonSite) == PythonSite.get_version

