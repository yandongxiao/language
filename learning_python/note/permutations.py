#!/usr/bin/env python
# encoding: utf-8

# NOTE: 当我们碰到看上去有些复杂的迭代问题时，最好可以先去看看itertools模块

a = [1,2,3]

# 3 * 2 * 1
# 这是一个排列问题
from itertools import permutations
for i in permutations(a):
    print i

# C3-2
# 这是一个组合问题: 即(1, 2) == (2, 1)
from itertools import combinations
for i in combinations(a, 2):
    print i

# 3 * 2
# 这是一个什么问题?
from itertools import combinations_with_replacement
for i in combinations_with_replacement(a, 2):
    print i
