#! /usr/bin/env python3
# encoding: utf-8

# NOTE: exec在python3中大变样
# 实际上对于 exec() 的正确使用是比较难的。大多数情况下当你要考虑使用 exec() 的时候
# 应该采用更好的解决办法

def test():
    a = 13
    loc = locals()      # 获取局部变量字典
    exec('b = a + 1')
    b = loc['b']
    assert b == 14

def test1():
    x = 0
    exec('x += 1')
    assert x == 0

def test2():
    x = 0
    loc = locals()
    print('before:', loc)
    exec('x += 1')
    print('after:', loc)
    assert x == 0
    assert loc['x'] == 1

def test3():
    x = 0
    loc = locals()
    assert loc['x'] == 0
    exec('x += 1')
    assert loc['x'] == 1
    locals()
    assert loc['x'] == 0

def test4():
    a = 13
    loc = { 'a' : a }
    glb = { }
    exec('b = a + 1', glb, loc)
    b = loc['b']
    assert b == 14

if __name__ == '__main__':
    print(':::: Running test()')
    test()

    print(':::: Running test1()')
    test1()

    print(':::: Running test2()')
    test2()

    print(':::: Running test3()')
    test3()

    print(':::: Running test4()')
    test4()
