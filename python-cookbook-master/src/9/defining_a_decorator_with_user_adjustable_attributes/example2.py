#! /usr/bin/env python3
# encoding: utf-8

# Alternate formulation using function attributes directly

from functools import wraps
import logging

def logged(level, name=None, message=None):
    '''
    Add logging to a function.  level is the logging
    level, name is the logger name, and message is the
    log message.  If name and message aren't specified,
    they default to the function's module and name.
    '''
    def decorate(func):
        logname = name if name else func.__module__
        log = logging.getLogger(logname)
        logmsg = message if message else func.__name__
        @wraps(func)
        def wrapper(*args, **kwargs):
            wrapper.log.log(wrapper.level, wrapper.logmsg)
            return func(*args, **kwargs)

        # Attach adjustable attributes
        # 这个方法也可能正常工作，但前提是它必须是最外层的装饰器才行。
        # 如果它的上面还有另外的装饰器(比如上面提到的 @timethis 例子)，那么它会隐藏底层属性，
        # 使得修改它们没有任何作用。 而通过使用访问函数就能避免这样的局限性。
        # 就先记住吧
        wrapper.level = level
        wrapper.logmsg = logmsg
        wrapper.log = log

        return wrapper
    return decorate

# Example use
@logged(logging.DEBUG)
def add(x, y):
    return x + y

@logged(logging.CRITICAL, 'example')
def spam():
    print('Spam!')

if __name__ == '__main__':
    import logging
    logging.basicConfig(level=logging.DEBUG)
    print(add(2, 3))

    # Change the log message
    add.logmsg = 'Add called'
    print(add(2, 3))

    # Change the log level
    add.level = logging.WARNING
    print(add(2, 3))
