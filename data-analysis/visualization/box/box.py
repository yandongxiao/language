# -*- coding: utf-8 -*-

import numpy as np
import matplotlib.pyplot as plt
import pandas as pd
import seaborn as sns

df=pd.read_csv("../lineplot/data.csv")
sns.boxplot(df['count'])
plt.show()

