#!/usr/bin/env python
# encoding: utf-8

# 1. a import b import c, 但是在main.py中只能引用b模块的内容
# 2. sys.path默认包含当前目录：注意是main.py所在的目录, python path/main.py也是可以的

import a
print(a.X)
