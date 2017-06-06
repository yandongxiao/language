# 一个函数中需要有一个 yield 语句即可将其转换为一个生成器
# 不需要return语句
# 生成器只能用于迭代操作
def frange(start, stop, increment):
    x = start
    while x < stop:
        yield x
        x += increment

for n in frange(0, 4, 0.5):
    print(n)
