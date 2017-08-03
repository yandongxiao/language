#!/usr/bin/env python
# encoding: utf-8

# 测试文件本身单独可执行

import unittest      # 名称是unittest
import sum

# 跳过整个测试类
#@unittest.expectedFailure
class TestSum(unittest.TestCase):   # 继承自unittest.TestCase

    def setUp(self):
        print "setup"

    # 如果测试失败，就会抛出异常，unittest会将这个测试标记为Failure
    # Errors是由于代码本身的错误引起, 比如import的模块还没有实现完全
    #
    def test_sum_by_int(self):
        self.assertEqual(sum.sum(1, 2), 4)  # Failure

    @unittest.skip("know failure")
    def test_sum_by_inst(self):
        self.assertEqual(sum.sum('a', 'b'), 4)  # Error

    def test_sum_by_str(self):
        self.assertEqual(sum.sum('a', 'b'), 'ab')

# main方法给测试脚本提供了命令行接口
if __name__ == '__main__':
    unittest.main()

# 替换方法
# 对命令行的支持就不是很友好
#suite = unittest.TestLoader().loadTestsFromTestCase(TestSum)
#unittest.TextTestRunner(verbosity=2).run(suite)

def mysuite():
    # 等价于
    # 1. suite = unittest.TestLoader().loadTestsFromTestCase(TestSum)
    #
    # tests = ['test_sum_by_int', 'test_sum_by_str']
    # return unittest.TestSuite(map(TestSum, tests))
    suite = unittest.TestSuite()
    suite.addTest(TestSum('test_sum_by_int'))
    suite.addTest(TestSum('test_sum_by_str'))
    return suite
#unittest.TextTestRunner(verbosity=2).run(mysuite())

