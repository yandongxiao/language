# -*- coding: utf-8 -*-

from sklearn import preprocessing
import numpy as np
# 初始化数据
x = np.array([[ 0., -3.,  1.],
              [ 3.,  1.,  2.],
              [ 0.,  1., -1.]])
# 将数据进行 Z-Score 规范化
# 结果是均值为0，方差为1的正太分布
scaled_x = preprocessing.scale(x)
print(scaled_x)

