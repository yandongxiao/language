单元测试最基本的结构应该是测试用例
测试用例就是unittest的TestCase类的一个实例
写测试代码时，必须书写TestCase的子类，或者使用FunctionTestCase

1. python test_sum.py
2. python -v test_sum.py
3. python -m unittest discover -v test      # 注意v的位置
4. python -m unittest test_sum2.TestSum
5. python -m unittest -v test_sum2.TestSum.test_sum_by_int
6. python -m unittest -h
7. python -m unittest discover -h
