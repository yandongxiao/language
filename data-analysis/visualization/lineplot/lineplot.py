# -*- coding: utf-8 -*-

import numpy as np
import pandas as pd
import seaborn as sns
import matplotlib.pyplot as plt

df = pd.read_csv("./data.csv")
sns.lineplot(x='ds', y='count', data=df)
plt.show()

