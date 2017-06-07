#!/usr/bin/env python
# encoding: utf-8

import pickle
from io import BytesIO

# 1. pickle 基本应用
f = BytesIO()
pickle.dump([1,2,3,4], f)
f.seek(0)   # very important
print(pickle.load(f))


# 2. 基本应用
f = BytesIO()
pickle.dump([1,2,3,4], f)
pickle.dump({"hello": "world"}, f)
f.seek(0)   # very important
print(pickle.load(f))
print(pickle.load(f))

#
