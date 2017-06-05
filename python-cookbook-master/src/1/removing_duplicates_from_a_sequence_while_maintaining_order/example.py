#! /usr/bin/python
# encoding: utf-8

# example.py
#
# Remove duplicate entries from a sequence while keeping order

# items是可遍历的对象
# 因为item需要被放到set当中，所以它必须是hashable的
def dedupe(items):
    seen = set()    # the element must can be hashed, 这是它的缺点
    for item in items:
        if item not in seen:
            yield item
            seen.add(item)

if __name__ == '__main__':
    a = [1, 5, 2, 1, 9, 1, 5, 10]
#    a = [
#        {'x': 2, 'y': 3},
#        {'x': 1, 'y': 4},
#        {'x': 2, 'y': 3},
#        {'x': 2, 'y': 3},
#        {'x': 10, 'y': 15}
#        ]

    print(a)
    print(list(dedupe(a)))
