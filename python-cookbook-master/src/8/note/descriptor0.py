#!/usr/bin/env python
# encoding: utf-8

# http://beginman.cn/python/2016/02/16/python-descriptor-guide/

class Ts(object):
    def __init__(self):
        self.a = 100
        self.b = 200

    def __set__(self, instance, value):
        print '__set__', instance, value
        return self

    # 如果不是通过实例访问，而是通过类访问的话，instance则为None
    # type(obj).__dict__['x'].__get__(obj, type(obj))
    # type(class).__dict__['x'].__get__(None, type(class))
    def __get__(self, instance, owner):
        print '__get__', instance, owner
        return self


class TTs(object):
    def __init__(self):

        # NOTE: 所谓的描述符就是实现了__get__和__set__方法的类
        # 同时实现__get__和__set__的称之为资料描述器（data descriptor）
        # 仅仅实现__get__的则为非描述器
        # 如果实例字典中有与描述器同名的属性，如果描述器是资料描述器，优先使用资料描述器，
        # 如果是非资料描述器，优先使用字典中的属性。
        # NOTE: 因为有__set__方法，所以它触发了该方法的调用
        self.x = 1000   # 会执行Ts的__set__方法
        self.y = 100
        self.z = 10

    x = Ts()    # 执行__init__方法
    y = 10
    a = 1


if __name__ == '__main__':
    t = TTs()
    print "======="
    # 在t对象中，t字典属性x和描述器属性同名x，则优先使用了资料描述器，
    # 所以t字典__dict__就没有x属性这一项
    # 这里涉及到另外的一个问题，即属性访问原理:
    # 1. 先访问对象的__dict__，如果没有再访问类（或父类，元类除外）的__dict__
    # 2. 如果类中__dict__的对象是一个描述器，则会调用描述器的__get__方法
    # NOTE: 实例的__dict__中的对象不可能是一个描述器
    print t.__dict__
    print t.x
    print t.y
    print t.a
