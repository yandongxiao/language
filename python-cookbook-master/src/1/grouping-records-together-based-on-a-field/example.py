#!/usr/bin/env python
# encoding: utf-8

"""
    Grouping records together based on a field.
"""

def doit():
    """doit"""
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

    # method - 1
    from collections import defaultdict
    rows_by_date = defaultdict(list)
    for row in rows:
        rows_by_date[row['date']].append(row)

    for key, vals in rows_by_date.items():
        print key,
        for val in vals:
            print val,
        print

    # method - 2
    # 注意groupby返回的是一个iterator
    rows = sorted(rows, key=lambda item: item['date'])
    from itertools import groupby
    for key, vals in groupby(rows, lambda row: row['date']):
        print key,
        for val in vals:
            print val,
        print

if __name__ == "__main__":
    doit()
