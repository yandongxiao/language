#! /usr/bin/env python
# encoding: utf-8

from socket import socket, AF_INET, SOCK_STREAM
from functools import partial

class LazyConnection:
    def __init__(self, address, family=AF_INET, type=SOCK_STREAM):
        self.address = address
        self.family = AF_INET
        self.type = SOCK_STREAM
        self.sock = None

    def __enter__(self):
        if self.sock is not None:
            raise RuntimeError('Already connected')
        self.sock = socket(self.family, self.type)
        self.sock.connect(self.address)
        return self.sock

    # 正常情况下，type，val，traceback 的输入都是None
    def __exit__(self, exc_ty, exc_val, trace):
        print "===", exc_ty
        print "===", exc_val
        print "===", trace, "=="
        self.sock.close()
        self.sock = None


if __name__ == '__main__':
    with LazyConnection(('www.python.org', 80)) as sock:
        # c.__enter__() executes: connection open
        sock.send(b'GET /index.html HTTP/1.0\r\n')
        sock.send(b'Host: www.python.org\r\n')
        sock.send(b'\r\n')
        resp = b''.join(iter(partial(sock.recv, 8192), b''))
        raise ValueError("no such value")
    print('Got %d bytes' % len(resp))
