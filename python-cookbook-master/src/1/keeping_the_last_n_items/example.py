#! /usr/bin/python
# encoding: utf-8

from collections import deque

# 注意previous_lines的应用
# yield不但返回了match的行，还返回了一个非常有用的列表
def search(lines, pattern, history=5):
    # 注意初始化它的方法, 更重要的是看懂help(deque)
    previous_lines = deque(maxlen=history)
    for line in lines:
        # 字符串竟然可以用in来表示包含关系
        if pattern in line:
            # search函数返回的是一个生成器
            yield line, previous_lines
        previous_lines.append(line)


# Example use on a file
if __name__ == '__main__':
    # with as 的工作原理：see http://blog.kissdata.com/2014/05/23/python-with.html
    # 1. 捕获异常；2. 关闭句柄
    with open('somefile.txt') as f:
        # f是一个可迭代的对象，每次返回文件一行的内容
        for line, prevlines in search(f, 'python', 5):
            for pline in prevlines:
                print pline,
            print line,
            print('-'*20)
