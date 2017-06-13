#!/usr/bin/env python
# encoding: utf-8

# python的协程可以类比LUA中的协程
# 协程最重要的特点是多个协程是在同一个线程下运行

def grep(pattern):
    # 生成器和协程都是用了yield关键字
    while True:
        line = yield
        if pattern in line:
            print line,

search = grep("print")
next(search)    # 启动协程

for line in open("lambda.py"):
    # send方法传递line给协程，并触发它运行
    # 这里grep确实没有什么必要实现成协程，实现为函数即可
    search.send(line)

search.close()  # NOTE: close it!!
