# -*- coding: utf-8 -*-

# 如何对多个变量，制作热图

import numpy as np
import matplotlib.pyplot as plt
import pandas as pd
import seaborn as sns

# contains duplicate entries, cannot reshape
# 说明数据不能包含相同的值
df=pd.read_csv("./data.csv")
data=df.pivot("year", "month", 'passengers')
# 用 Seaborn 画热力图
sns.heatmap(data)
plt.show()

