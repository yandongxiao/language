#!/usr/bin/env python3
# encoding: utf-8

def abs(n):
    '''
    Function to get absolute value of number.

    Example:

    >>> abs(1)
    -1
    >>> abs(-1)
    1
    >>> abs(0)
    0
    '''
    return n if n >= 0 else (-n)

# 这是文档测试的好地方
if __name__ == "__main__":
    import doctest
    doctest.testmod()
