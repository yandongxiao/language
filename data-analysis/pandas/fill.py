# -*- coding: utf-8 -*-

# 使用均值来填充
df['Age'].fillna(df['Age'].mean(), inplace=True)

# 使用出现频次最高的值进行填充
age_maxf = train_features['Age'].value_counts().index[0]
train_features['Age'].fillna(age_maxf, inplace=True)

# 删除全空的行
df.dropna(how='all',inplace=True)
