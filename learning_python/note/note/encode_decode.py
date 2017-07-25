#!/usr/bin/env python
#! encoding: utf-8


# 1. encoding: utf-8 是关于python文件本身是采用何种编码方式写的代码
# 2. sys.getdefaultencoding()是系统默认的编码方式，在python3中也可以指定编码方式
# 3. see http://www.wklken.me/posts/2013/08/31/python-extra-coding-intro.html

# 解决在交互模式下报告UnicodeDecodeError: 'ascii' codec can't decode byte
#import sys
#reload(sys)
#sys.setdefaultencoding('utf8')

# 1. 读文件
# 2. 外部输入编码，decode转成unicode
# 3. 处理(内部编码，统一unicode)
# 4. encode转成需要的目标编码
# 5. 写到目标输出(文件或控制台)

# 为什么使用rt模式读取数据返回的对象的类型还是  str
with open("testfile.txt", "rb") as f:
    data = f.read()
    print(type(data))   # 以二进制形式读取的数据是编码后的str
    text = data.decode("utf-8")     # 解码
    print(type(text))   # 解码后的类型是unicode类型的内容
    print(text)         # 之所以这里会报错，就是因为python使用系统默认的ascii对unicode进行编码
    print(text.encode("utf-8")) # 这才是输出的正确姿势

with open("testfile.txt", "rt") as f:
    data = f.read()
    print(type(data))
