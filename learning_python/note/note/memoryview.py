#!/usr/bin/env python
# encoding: utf-8

# 使得它支持切片操作
buf = bytearray("helloworld")
m1 = memoryview(buf)
m1[:] = "nihaoshiji"    # 注意大小不能更改
print buf
