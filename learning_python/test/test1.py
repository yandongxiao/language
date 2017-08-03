#!/usr/bin/env python
# encoding: utf-8

import unittest

class JustForTest(unittest.TestCase):
    # 重写runTest方法
    def runTest(self):
        length = 10
        self.assertEqual(10, length)

    # 检查异常的方法
    def test_attrerror(self):
        with self.assertRaises(NameError):
            d = nihao

unittest.main()
