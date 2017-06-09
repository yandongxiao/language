#!/usr/bin/env python
# encoding: utf-8

# 让对象支持上下文管理协议

from socket import socket, AF_INET, SOCK_STREAM

class LazyConnection:
    def __init__(self, addr, family=AF_INET, type=SOCK_STREAM):
        self.addr = addr
        self.family = family
        self.type = type
        self.connections = []

    def __enter__(self):
        sock = socket(self.family, self.type)
        sock.connect(self.addr)
        self.connections.append(sock)
        return sock

    # 忽略异常则返回一个None值
    def __exit__(self, exc_type, exc_val, exc_tb):
        sock = self.connections.pop()
        sock.close()

from functools import partial

# 不管 with 代码块中发生什么，上面的控制流都会执行完，就算代码块中发生了异常也是一样的。
with LazyConnection(("www.baidu.com", 80)) as sock:
    sock.send(b"GET / HTTP/1.0\r\n")    # 注意有一个斜杠
    sock.send(b"HOST: www.baidu.com\r\n")
    sock.send(b"\r\n")

    resp = "".join(iter(partial(sock.recv, 1024), b''))

print "recevice bytes %d" % len(resp)
