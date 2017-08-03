#!/usr/bin/env python
# encoding: utf-8

# 测试文件本身单独可执行

import unittest      # 名称是unittest
import sum


class TestSum(unittest.TestCase):   # 继承自unittest.TestCase

    def setUp(self):
        print "setup"

    def test_sum_by_int(self):
        self.assertEqual(sum.sum(1, 2), 3)

    def test_sum_by_str(self):
        self.assertEqual(sum.sum('a', 'b'), 'ab')

# main方法给测试脚本提供了命令行接口
if __name__ == '__main__':
    unittest.main()

# 替换方法
# 对命令行的支持就不是很友好
#suite = unittest.TestLoader().loadTestsFromTestCase(TestSum)
#unittest.TextTestRunner(verbosity=2).run(suite)
