#! /usr/bin/python
# encoding: utf-8

# example2.py
#
# Remove duplicate entries from a sequence while keeping order

def dedupe(items, key=None):
    seen = set()
    for item in items:  # iterable object
        # 注意if/else的应用
        val = item if key is None else key(item)    # 获取hashable元素
        if val not in seen:
            yield item
            seen.add(val)

if __name__ == '__main__':
    a = [
        {'x': 2, 'y': 3},
        {'x': 1, 'y': 4},
        {'x': 2, 'y': 3},
        {'x': 2, 'y': 3},
        {'x': 10, 'y': 15}
        ]
    print a
    # 不要使用for/in的方式输出一个iterable对象
    print list(dedupe(a, key=lambda a: (a['x'], a['y'])))
