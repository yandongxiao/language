# -*- coding: utf-8 -*-

import matplotlib.pyplot as plt
import seaborn as sns
import pandas as pd
import ssl

ssl._create_default_https_context = ssl._create_unverified_context

# 数据准备
df=pd.read_csv("./data.csv")

# 用 Seaborn 画成对关系
sns.pairplot(df)
plt.show()
