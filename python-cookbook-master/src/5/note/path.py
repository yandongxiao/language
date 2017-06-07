#!/usr/bin/env python
# encoding: utf-8

import os

# NOTE:
# 对于任何的文件名的操作，你都应该使用 os.path 模块
# 而不是使用标准字符串操作来构造自己的代码。 特别是为了可移植性考虑的时候更应如此
# 你真的不应该浪费时间去重复造轮子
# 注意PermissionError错误
os.path.exists('/etc/passwd')
os.path.exists('/tmp/spam')
os.path.isfile('/etc/passwd')
os.path.isdir('/etc/passwd')
os.path.getsize('/etc/passwd')

