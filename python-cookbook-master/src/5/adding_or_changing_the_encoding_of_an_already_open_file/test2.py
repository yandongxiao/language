#!/usr/bin/env python3
# encoding: utf-8

import os
import io


#文件描述符的封装结构：
#1. io.TextIOWrapper 是一个编码和解码Unicode的文本处理层
#2. io.BufferedWriter 是一个处理二进制数据的带缓冲的I/O层
#3. io.FileIO 是一个表示操作系统底层文件描述符的原始文件。
# NOTE: 在这里latin是3层对象，一个文件描述符有且只有一个三层对象
# 主要是为了说明detach的作用
latin = open("testfile.txt", "rt", encoding="latin-1")
f = io.TextIOWrapper(latin.detach(), "utf-8")
print(f.read())
