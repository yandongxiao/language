# -*- coding: utf-8 -*-

import numpy as np

x1 = np.arange(1,11,2)  # 1 3 5 7 9
x2 = np.linspace(1,9,5) # 1 3 5 7 9
print np.add(x1, x2)
print np.subtract(x1, x2)
print np.multiply(x1, x2)
print np.divide(x1, x2)
print np.power(x1, x2)
print np.remainder(x1, x2)
