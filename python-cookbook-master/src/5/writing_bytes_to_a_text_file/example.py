#! /usr/bin/env python3

# Example of writing raw bytes on a file opened in text mode
# I/O系统以层级结构的形式构建而成
# 文本文件是通过在一个拥有缓冲的二进制模式文件上增加一个Unicode编码/解码层来创建。
# 所以本质上写到底层的都是编码过的
# NOTE: python3的特性
import sys
data = b'Hello World\n'
sys.stdout.buffer.write(data)


with open("testfile.txt", "wt") as f:
    f.buffer.write(data)
