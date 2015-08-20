#! /usr/bin/env python3

# Find symbolic links and show where they point to.
# Arguments are directories to search; default is current directory.
# No recursion.
# (This is a totally different program from "findsymlinks.py"!)

import sys, os

def lll(dirname):
    for name in os.listdir(dirname):            #包含了'.' 和 '..'目录
        if name not in (os.curdir, os.pardir):
            full = os.path.join(dirname, name)
            if os.path.islink(full):
                print(name, '->', os.readlink(full))   #读取软链接的目标文件路径


def main():
    args = sys.argv[1:]
    if not args: args = [os.curdir] 	#os.curdir, 目前来说是'.'，可调用os.path.abspath('.')转换为绝对路径
    first = 1
    for arg in args:		#为了标识输出信息是哪一个目录的
        if len(args) > 1:
            if not first: print()
            first = 0
            print(arg + ':')
        lll(arg)           #这里是原文的一个小bug吧.

if __name__ == '__main__':
    main()
