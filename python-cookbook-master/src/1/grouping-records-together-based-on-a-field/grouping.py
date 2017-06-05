#! /usr/bin/python
# encoding: utf-8

rows = [
    {'address': '5412 N CLARK', 'date': '07/01/2012'},
    {'address': '5148 N CLARK', 'date': '07/04/2012'},
    {'address': '5800 E 58TH', 'date': '07/02/2012'},
    {'address': '2122 N CLARK', 'date': '07/03/2012'},
    {'address': '5645 N RAVENSWOOD', 'date': '07/02/2012'},
    {'address': '1060 W ADDISON', 'date': '07/02/2012'},
    {'address': '4801 N BROADWAY', 'date': '07/01/2012'},
    {'address': '1039 W GRANVILLE', 'date': '07/04/2012'},
]

from itertools import groupby

# 先按照日期进行排序对groupby函数是必要的，排序意味着需要更多的CPU
# groupby函数扫描整个序列并且查找连续相同值的元素序列
rows.sort(key=lambda r: r['date'])
for date, items in groupby(rows, key=lambda r: r['date']):
    print(date)
    for i in items:
        print('    ', i)

# Example of building a multidict
# 也是按照日期进行分类的方法, 但是使用dict就会占用更多的内存，且访问顺序被打乱了
from collections import defaultdict
rows_by_date = defaultdict(list)
for row in rows:
    rows_by_date[row['date']].append(row)

for r in rows_by_date['07/01/2012']:
    print(r)

new_rows_by_date = {}
for row in rows :
    new_rows_by_date[row['date']] = row #another same date element will replace it.
print new_rows_by_date
