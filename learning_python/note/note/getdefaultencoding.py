#!/usr/bin/env python
# encoding: utf-8

# 第二行的重要性
# Non-ASCII character '\xe4' in file getdefaultencoding.py on line 4

# python2 上默认的系统编码是ascii
# python3 上默认的系统编码是utf-8
import sys
print(sys.getdefaultencoding())


# open函数会将Windows和Unix的换行符统一转换为\n
# 通过newline参数可以改变这一行为, 即newline="",并不是改变了
# python对于行尾的认知，而是如果windows读取文件内容是，\r\n被完整保留
# python3的特性
# 不是任意字符都可以是newline的值的，illegal newline value: o
with open("testfile.txt", "rt") as f:   # t表示以文本形式打开
    for line in f:
        print(line),
