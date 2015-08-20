#! /usr/bin/env python3

# suff
#
# show different suffixes amongst arguments

import sys


def main():
    files = sys.argv[1:]
    suffixes = {}            #字典
    for filename in files:
        suff = getsuffix(filename)
        '''
		这里的空格需要注意
		>>> yyy={}
		>>> rs = yyy.setdefault(aaa,[]), 如果不存在key=aaa,那么设置key=aaa，value=[].如果存在，则直接返回value的值.
		>>> rs
		[]
		>>> yyy
		{aaa: []}
		>>> rs.append(1)	#下面的内容顺利成章
		>>> rs
		[1]
		>>> yyy
		{aaa: [1]}

        '''
        suffixes.setdefault(suff, []).append(filename)
		
        '''
			>>> yyy.items()		#items()函数返回一个列表，列表中每个元素是一个元组
			[('aaa', [1])]

        '''
    for suff, filenames in sorted(suffixes.items()):
        print(repr(suff), len(filenames))         #repr可显示出非打印字符


def getsuffix(filename):
    '''
		help上说是built-in function，但是不管如何挺好用的，返回一个元组。
		元组的返回值用这种特别的方式接收.
    '''
    name, sep, suff = filename.rpartition('.')       

	
    '''
		这样应用 if/else 更像是在说话.
    '''
    return sep + suff if sep else ''


if __name__ == '__main__':
    main()
