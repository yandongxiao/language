#! /usr/bin/env python3
# Example of adding a text encoding to existing file-like object

import urllib.request
import io

# 以二进制形式打开的类文件对象
u = urllib.request.urlopen('http://www.python.org')

# 第一个参数是类文件对象
f = io.TextIOWrapper(u, encoding='utf-8')   # 封装一个encoding和decoding
text = f.read()
print(text)
