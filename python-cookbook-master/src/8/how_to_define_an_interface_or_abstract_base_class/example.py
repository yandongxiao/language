#! /usr/bin/env python3
# encoding: utf-8

# Defining a simple abstract base class

from abc import ABCMeta, abstractmethod

class IStream(metaclass=ABCMeta):
    @abstractmethod
    def read(self, maxbytes=-1):
        pass
    @abstractmethod
    def write(self, data):
        pass

# Example implementation
# 一种方法是主动继承抽象基类
class SocketStream(IStream):
    def read(self, maxbytes=-1):
        print('reading')
    def write(self, data):
        print('writing')

# Example of type checking
def serialize(obj, stream):
    if not isinstance(stream, IStream):
        raise TypeError('Expected an IStream')
    print('serializing')

# Examples
if __name__ == '__main__':
    # Attempt to instantiate ABC directly (doesn't work)
    try:
        a = IStream()
    except TypeError as e:
        print(e)

    # Instantiation of a concrete implementation
    a = SocketStream()
    a.read()
    a.write('data')

    # Passing to type-check function
    serialize(None, a)      # 传递一个抽象基类的子类

    # Attempt to pass a file-like object to serialize (fails)
    import sys
    try:
        serialize(None, sys.stdout)
    except TypeError as e:
        print(e)
    print("==================")

    # 第二种方法是主动注册
    # Register file streams and retry
    # 利用register方法将类对象进行归类时，不需要类对象实现任何特殊方法
    # 归类的目的是为了利用isinstance 和 issubclass
    import io
    IStream.register(io.IOBase)
    serialize(None, sys.stdout)
