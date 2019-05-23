# -*- coding: utf-8 -*-

import numpy as np
import pandas as pd
import seaborn as sns
import matplotlib.pyplot as plt

df = pd.read_csv("./sku_count.csv")
df = df[df.outstore_count < 10]

# scatter图像适合统计数据较少的情况下，来发现横坐标和纵坐标之间的关系。
sns.jointplot(x="sku_id", y="outstore_count", data=df, kind='scatter');
plt.show()
