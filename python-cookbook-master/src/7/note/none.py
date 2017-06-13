#!/usr/bin/env python
# encoding: utf-8

def test_none(arg = None):
    # 测试arg的正确方法
    if arg is None:
        print "用户没有提供参数"

    if not arg:
        print "empty不表示用户没有提供参数"

test_none(0)
