# -*- coding: utf-8 -*-

import numpy as np
import pandas as pd
import seaborn as sns
import matplotlib.pyplot as plt

df = pd.read_csv("../scatter/sku_count.csv")
df = df[df.outstore_count < 10]

sns.jointplot(x="sku_id", y="outstore_count", data=df, kind='kde');
plt.show()

