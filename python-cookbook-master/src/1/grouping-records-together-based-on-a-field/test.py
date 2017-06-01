#!/usr/bin/env python
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


# method1
rows.sort(key=lambda r: r['date'])
date = rows[0]['date']
print date
for r in rows:
    if date != r['date']:
        date = r['date']
        print date
    print('    ', r)


# method2
from collections import defaultdict
rows_by_date = defaultdict(list)
date = rows[0]['date']
for r in rows:
    if date != r['date']:
        date = r['date']
    rows_by_date[date].append(r)

for key, rows in rows_by_date.items():
    print key
    for row in rows:
        print('    ', row)


