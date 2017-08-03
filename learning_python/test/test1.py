#!/usr/bin/env python
# encoding: utf-8

import unittest

class JustForTest(unittest.TestCase):
    # 重写runTest方法
    def runTest(self):
        length = 10
        self.assertEqual(10, length)

unittest.main()
