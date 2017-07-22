#! /usr/bin/env python3
# example.py
#
# Example of combining dicts into a chainmap

a = {'x': 1, 'z': 3 }
b = {'y': 2, 'z': 4 }

# (a) Simple example of combining
# 1. ChainMap并没有创建一个新的Map
# 2. 如果出现重复键，那么第一次出现的映射值会被返回
# 3. 在a和b表上的修改会映射到c表上
from collections import ChainMap
c = ChainMap(a,b)
assert c['x'] == 1
assert c['y'] == 2
assert c['z'] == 3
assert len(c) == 3

# Modify some values
# 对于字典的更新或删除操作总是影响的是列表中第一个字典
c['z'] = 10
c['w'] = 40
del c['x']
assert a['z'] == 10
assert a['w'] == 40
assert len(a) == 2

c['y'] = 100
assert a['y'] == 100
assert len(a) == 3
assert c['y'] == 100
assert b['y'] == 2


# Example of stacking mappings (like scopes)
values = ChainMap()
values['x'] = 1

# Add a new mapping
values = values.new_child()
values['x'] = 2

# Add a new mapping
values = values.new_child()
values['x'] = 3

print(values)
print(values['x'])

# Discard last mapping
values = values.parents
print(values)
print(values['x'])

# Discard last mapping
values = values.parents
print(values)
print(values['x'])

values = values.new_child()
