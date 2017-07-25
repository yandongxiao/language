#! /usr/bin/env python3
# encoding: utf-8
# Example of faking classes with a closure

# 使用闭包来模拟类
import sys
class ClosureInstance:
    def __init__(self, locals=None):
        if locals is None:
            # local name space. It is a dict, with name and value in the space.
            locals = sys._getframe(1).f_locals

        # Update instance dictionary with callables
        # __dict__ 是实例对象的属性和方法的字典，我们可以通过点运算符，del来添加和删除属性
        # 也可以直接操作__dict__字典
        self.__dict__.update((key,value) for key, value in locals.items()
                             if callable(value) )   #( ) is a generator

    # Redirect special methods
    # 之所以要重定向，是因为Stake当中的__len__作为了实例的一个属性而存在
    # len() 调用的是类对象的方法
    def __len__(self):
        return self.__dict__['__len__']()

# Example use
def Stack():
    items = []

    def push(item):
        items.append(item)

    def pop():
        return items.pop()      #return the poped value

    def __len__():
        return len(items)

    return ClosureInstance()

if __name__ == '__main__':
    s = Stack()
    s.push(10)
    s.push(20)
    s.push('Hello')
    print(len(s))
    print(s.pop())
    print(s.pop())
    print(s.pop())
