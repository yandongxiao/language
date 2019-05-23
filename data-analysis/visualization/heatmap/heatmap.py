# -*- coding: utf-8 -*-

# 如何对多个变量，制作热图

import numpy as np
import matplotlib.pyplot as plt
import pandas as pd
import seaborn as sns

# 数据准备
skus = np.genfromtxt("../scatter/example.csv", delimiter=",", skip_header=1)
#df = pd.DataFrame({'id': skus[:,0], 'count': skus[:,1]})
#print(df)
# 用 Seaborn 画热力图
sns.heatmap(skus)
plt.show()

