# -*- coding: utf-8 -*-

import numpy as np
import pandas as pd
import seaborn as sns
import matplotlib.pyplot as plt

skus = np.genfromtxt("sku_count.csv", delimiter=",", skip_header=1)
df = pd.DataFrame({'x': skus[:,0], 'y': skus[:,1]})
sns.jointplot(x="x", y="y", data=df, kind='scatter');
plt.show()

