#!/usr/bin/env python
# encoding: utf-8

import heapq

# 这种排序算法称为归并排序
l1 = [1, 3, 5, 7]
l2 = [2, 4, 6, 8]
print list(heapq.merge(l1, l2))
