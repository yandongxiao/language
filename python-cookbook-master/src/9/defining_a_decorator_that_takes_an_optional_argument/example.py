#! /usr/bin/env python3
# encoding: utf-8

from functools import wraps, partial
import logging

# 选项参数都已经有了默认参数
def logged(func=None, *, level=logging.DEBUG, name=None, message=None):
    if func is None:
        return partial(logged, level=level, name=name, message=message)

    logname = name if name else func.__module__
    log = logging.getLogger(logname)
    logmsg = message if message else func.__name__
    @wraps(func)
    def wrapper(*args, **kwargs):
        log.log(level, logmsg)
        return func(*args, **kwargs)
    return wrapper


# Example use
@logged     # func is not None
def add(x, y):
    return x + y


# func is None
# logged = partial(logged, level=level, name=name, message=message)
# sub = logged(sub)
@logged()       # 支持这种形式后，解决编程一致性问题
def sub(x, y):
    return x - y


# l = logged(...)   因为func是None值，所以返回的是partial的返回值
# s = l(spam)
@logged(level=logging.CRITICAL, name='example')
def spam():
    print('Spam!')

if __name__ == '__main__':
    import logging
    logging.basicConfig(level=logging.DEBUG)
    add(2,3)
    sub(2,3)
    spam()
